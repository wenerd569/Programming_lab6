#include "frontend/reqest_sender.hpp"
#include <boost/asio/any_io_executor.hpp>
#include <boost/asio/co_spawn.hpp>
#include <boost/asio/io_context.hpp>
#include <boost/asio/steady_timer.hpp>
#include <boost/beast.hpp>
#include <boost/beast/websocket/stream.hpp>
#include <boost/system/error_code.hpp>
#include <functional>
#include <mutex>

using namespace std::chrono_literals;

RequestSender::RequestSender(websocket::stream<tcp::socket> ws) : ws { std::move(ws) }
{
}

asio::awaitable<json>
RequestSender::waitForResponce(long id,
                               std::unordered_map<int, std::function<void(json)>> &pending,
                               std::mutex &mtx)
{
    auto executor = co_await asio::this_coro::executor;
    asio::steady_timer timer(executor);
    timer.expires_after(std::chrono::seconds(10));

    boost::system::error_code ec;
    json result;

    bool done = false;
    asio::use_awaitable_t<> token = asio::use_awaitable;

    co_return co_await asio::async_initiate<asio::use_awaitable_t<>, void(json)>(
        [id, &done, &timer, &mtx, &pending] (auto &&handler) mutable {
            {
                std::scoped_lock lock(mtx);
                pending[id] = [handler = std::move(handler), &done, &timer] (json data) mutable {
                    if ( done ) {
                        return;
                    }
                    done = true;
                    timer.cancel();
                    handler(std::move(data));
                };
            }

            timer.async_wait([id, &done, &mtx, &pending] (boost::system::error_code ec) {
                if ( done ) {
                    return;
                }
                done = true;

                std::function<void(json)> cb;
                {
                    std::scoped_lock lock(mtx);
                    if ( auto it = pending.find(id); it != pending.end() ) {
                        cb = std::move(it->second);
                        pending.erase(it);
                    }
                }

                if ( cb ) {
                    cb(json { "" });  // todo
                }
            });
        },
        token);
}