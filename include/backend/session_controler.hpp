#pragma once

#include "backend/session.hpp"
#include <boost/asio.hpp>
#include <boost/asio/awaitable.hpp>
#include <boost/asio/steady_timer.hpp>
#include <boost/asio/use_awaitable.hpp>
#include <boost/beast/websocket.hpp>
#include <chrono>
#include <memory>
#include <mutex>
#include <unordered_set>

using tcp = boost::asio::ip::tcp;
using namespace std::chrono_literals;

class SessionManager : public std::enable_shared_from_this<SessionManager> {
    using milliseconds = std::chrono::milliseconds;

private:
    boost::asio::steady_timer timer;
    milliseconds checkInterval;
    milliseconds sessionTimeout;

    std::unordered_set<std::weak_ptr<Session>, std::owner_less<std::weak_ptr<Session>>> sessions;

    std::mutex mtx;

public:
    static std::shared_ptr<SessionManager>
    create (boost::asio::io_context &io_context,
            milliseconds checkInterval = milliseconds(10000),
            milliseconds sessionTimeout = milliseconds(30000));

    void addSession (const std::shared_ptr<Session> &session);

private:
    SessionManager(boost::asio::io_context &io_context,
                   milliseconds check_interval,
                   milliseconds session_timeout);

    boost::asio::awaitable<void> monitor ();
};