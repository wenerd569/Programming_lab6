
#include <boost/asio.hpp>
#include <boost/asio/awaitable.hpp>
#include <boost/asio/io_context.hpp>
#include <boost/asio/steady_timer.hpp>
#include <boost/beast/websocket.hpp>
#include <nlohmann/json.hpp>
#include <nlohmann/json_fwd.hpp>

namespace asio = boost::asio;
namespace beast = boost::beast;
namespace websocket = beast::websocket;
using tcp = asio::ip::tcp;
using json = nlohmann::json;

// что-то, что управляет websoket'ом
class Session {
    std::chrono::steady_clock::time_point lastActivity;
    bool active;

protected:
    websocket::stream<tcp::socket> ws;
    beast::flat_buffer buffer;

public:
    Session(websocket::stream<tcp::socket> ws);
    std::chrono::steady_clock::time_point getLastActivityTime () const;
    bool isActive () const;
    boost::asio::awaitable<void> close ();

    boost::asio::awaitable<json> readJson ();

    boost::asio::awaitable<void> sendJson (const json &j);

    virtual ~Session() = default;

protected:
    void updateLastActivity ();
};

#include <boost/beast/core.hpp>

asio::awaitable<nlohmann::json> Session::readJson()
{
    buffer.consume(buffer.size());
    co_await ws.async_read(buffer, boost::asio::use_awaitable);
    updateLastActivity();
    std::string s = beast::buffers_to_string(buffer.data());
    co_return nlohmann::json::parse(s);
}

boost::asio::awaitable<void> Session::sendJson(const nlohmann::json &j)
{
    std::string dump = j.dump();
    co_await ws.async_write(boost::asio::buffer(dump), boost::asio::use_awaitable);
    updateLastActivity();
}

Session::Session(websocket::stream<tcp::socket> ws) : ws { std::move(ws) } {};

bool Session::isActive() const
{
    return active;
}

std::chrono::steady_clock::time_point Session::getLastActivityTime() const
{
    return lastActivity;
}

void Session::updateLastActivity()
{
    lastActivity = std::chrono::steady_clock::now();
}

boost::asio::awaitable<void> Session::close()
{
    if ( ws.is_open() ) {
        co_await ws.async_close(websocket::close_code::normal, boost::asio::use_awaitable);
    }
    active = false;
}