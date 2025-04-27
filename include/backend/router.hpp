#pragma once

#include <boost/asio/awaitable.hpp>
#include <string>
#include <unordered_map>

namespace asio = boost::asio;

class Router {
public:
    using Handler = std::function<asio::awaitable<void>()>;

    void addRoute (std::string path, Handler handler);

    Handler resolve (std::string path);

private:
    std::unordered_map<std::string, Handler> routes;
};

Router::Handler Router::resolve(std::string path)
{
    auto it = routes.find(path);
    if ( it != routes.end() ) {
        return it->second;
    }
}

void Router::addRoute(std::string path, Router::Handler handler)
{
    routes[path] = handler;
}
