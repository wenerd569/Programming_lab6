#pragma once

#include "common/command_call_request.hpp"
#include "common/from_to_json.hpp"
#include "common/response.hpp"
#include <boost/asio.hpp>
#include <boost/asio/awaitable.hpp>
#include <boost/asio/io_context.hpp>
#include <boost/asio/registered_buffer.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/beast/websocket/stream.hpp>

namespace asio = boost::asio;
namespace beast = boost::beast;
namespace websocket = beast::websocket;
using tcp = asio::ip::tcp;

class RequestSender {
    websocket::stream<tcp::socket> ws;
    std::mutex mtx;
    std::unordered_map<int, std::function<void(json)>> pending;
    std::atomic<long> id = 0;

public:
    RequestSender(websocket::stream<tcp::socket> ws);

    template<typename T, typename... Args>
    asio::awaitable<Response<T>> sendCommand (CommandCallRequest<Args...> command);

private:
    asio::awaitable<json>
    waitForResponce (long id,
                     std::unordered_map<int, std::function<void(json)>> &pending,
                     std::mutex &mtx);
};

template<typename T, typename... Args>
asio::awaitable<Response<T>> RequestSender::sendCommand(CommandCallRequest<Args...> command)
{
    long req_id = id++;
    command.reqestId = req_id;

    nlohmann::json j = command;
    std::string data = j.dump();
    co_await ws.async_write(asio::buffer(data), asio::use_awaitable);
    json json_res = co_await waitForResponce(req_id, pending, mtx);
    Response<T> res;
    json_res.get_to(res);
    co_return res;
}
