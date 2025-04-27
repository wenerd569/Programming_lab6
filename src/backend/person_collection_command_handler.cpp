#include "backend/person_collection_command_handler.hpp"

#include "common/command_call_request.hpp"
#include "common/from_to_json.hpp"
#include "common/response.hpp"
#include <boost/asio/awaitable.hpp>
#include <boost/asio/co_spawn.hpp>
#include <boost/asio/use_awaitable.hpp>
#include <boost/beast/websocket/stream.hpp>
#include <memory>
#include <string>

template<typename Controller, typename T, typename... Args>
std::function<json(json &)>
makeHandler (std::shared_ptr<Controller> ctrl, Response<T> (Controller::*method)(Args...))
{
    return [ctrl, method] (json &j_in) -> json {
        try {
            auto req = CommandCallRequest<Args...>::from_json(j_in);
            auto tup = req.getArguments();

            Response<T> res = std::apply(
                [&] (Args &&...unpacked) {
                    return (ctrl.get()->*method)(std::forward<Args>(unpacked)...);
                },
                tup);

            res.setRequestId(req.getRequestId());

            // 5. Сериализуем обратно в JSON
            return Response<T>::to_json(res);
        } catch ( const nlohmann::json::exception &e ) {

            auto err = Response<T>::failure(ResponseCode::INCORRECT_REQUESTION);
            if ( j_in.contains("reqestId") && j_in.at("reqestId").is_number_integer() ) {
                err.setRequestId(j_in.at("reqestId").get<long>());
            }
            return Response<T>::to_json(err);
        }
    };
}

std::unordered_map<std::string, std::function<json(json)>>
initRouter (std::shared_ptr<CollectionManager> collectionManager)
{
    std::unordered_map<std::string, std::function<json(json)>> comandRouter {};
    comandRouter.emplace("add", makeHandler(collectionManager, &CollectionManager::add));
    return comandRouter;
}

PersonCollectionCommandHandler::PersonCollectionCommandHandler(
    const asio::io_context::executor_type &ioc_executor,
    std::shared_ptr<CollectionManager> collectionManager)
    : collectionManager { collectionManager }, ioc_executor { ioc_executor }
{
    comandRouter = std::move(initRouter(collectionManager));
}

asio::awaitable<void> PersonCollectionCommandHandler::startHandling(std::shared_ptr<Session> sesion)
{
    while ( sesion->isActive() ) {
        json j = co_await sesion->readJson();
        json res;
        if ( j.contains("commandName") && j.at("commandName").is_string() ) {
            res = comandRouter[j.at("commandName").get<std::string>()](j);
        } else {
            Response<void> resp = Response<void>::failure(ResponseCode::INCORRECT_REQUESTION);
            if ( j.contains("reqestId") && j.at("reqestId").is_number_integer() ) {
                resp.setRequestId(j.at("reqestId").get<long>());
            }
            res = Response<void>::to_json(resp);
        }
        co_await sesion->sendJson(res);
    }
}

std::shared_ptr<Session>
PersonCollectionCommandHandler::startSession(websocket::stream<tcp::socket> ws)
{
    std::shared_ptr<Session> res = std::make_shared<Session>(ws);
    asio::co_spawn(ioc_executor, startHandling(res), asio::detached);
    return res;
}
