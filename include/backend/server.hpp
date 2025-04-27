#pragma once

#include <boost/asio/awaitable.hpp>
#include <boost/asio/io_context.hpp>
#include <boost/beast/websocket/stream.hpp>
#include <memory>

#include "backend/person_collection_command_handler.hpp"

class Server {
    const asio::io_context::executor_type &ioc_executor;
    PersonCollectionCommandHandler handler;
    tcp::acceptor acceptor;

public:
    Server(const asio::io_context::executor_type &ioc_executor,
           uint16_t port,
           std::shared_ptr<CollectionManager> collectionManager);

    asio::awaitable<void> start ();
};