#pragma once

#include "backend/session_controler.hpp"

std::shared_ptr<SessionManager> SessionManager::create(boost::asio::io_context &io_context,
                                                       milliseconds checkInterval,
                                                       milliseconds sessionTimeout)
{
    auto mgr = std::shared_ptr<SessionManager>(
        new SessionManager(io_context, checkInterval, sessionTimeout));
    boost::asio::co_spawn(
        io_context,
        [mgr] () -> boost::asio::awaitable<void> {
            co_await mgr->monitor();
        },
        boost::asio::detached);
    return mgr;
}

void SessionManager::addSession(const std::shared_ptr<Session> &session)
{
    std::lock_guard<std::mutex> lock(mtx);
    sessions.insert(session);
}

SessionManager::SessionManager(boost::asio::io_context &io_context,
                               milliseconds check_interval,
                               milliseconds session_timeout)
    : timer(io_context), checkInterval(check_interval), sessionTimeout(session_timeout)
{
}

boost::asio::awaitable<void> SessionManager::monitor()
{
    auto executor = co_await boost::asio::this_coro::executor;
    while ( true ) {
        timer.expires_after(checkInterval);
        co_await timer.async_wait(boost::asio::use_awaitable);

        auto now = std::chrono::steady_clock::now();
        std::lock_guard<std::mutex> lock(mtx);

        for ( auto it = sessions.begin(); it != sessions.end(); ) {
            if ( auto session = it->lock() ) {
                if ( now - session->getLastActivityTime() > sessionTimeout ) {
                    // Закрываем сессию асинхронно
                    boost::asio::co_spawn(
                        executor,
                        [session] () -> boost::asio::awaitable<void> {
                            co_await session->close();
                        },
                        boost::asio::detached);
                    it = sessions.erase(it);
                    continue;
                }
                ++it;
            } else {
                it = sessions.erase(it);
            }
        }
    }
}