#include "backend/colection_manager.hpp"
#include "backend/session.hpp"
#include <boost/asio/awaitable.hpp>
#include <boost/asio/io_context.hpp>
#include <boost/beast/websocket/stream.hpp>
#include <functional>
#include <memory>
#include <unordered_map>

class PersonCollectionCommandHandler {
    const asio::io_context::executor_type &ioc_executor;
    std::shared_ptr<CollectionManager> collectionManager;
    std::unordered_map<std::string, std::function<json(json)>> comandRouter;

public:
    std::shared_ptr<Session> startSession (websocket::stream<tcp::socket> ws);

    PersonCollectionCommandHandler(const asio::io_context::executor_type &ioc,
                                   std::shared_ptr<CollectionManager> collectionManager);

private:
    asio::awaitable<void> startHandling (std::shared_ptr<Session> sesion);
};