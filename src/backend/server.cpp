#include "backend/server.hpp"

asio::awaitable<void> Server::start()
{
    while ( 1 ) {
        tcp::socket socket { ioc_executor };
        acceptor.accept(socket);
        websocket::stream<tcp::socket> ws { socket };
        handler.startSession(std::move(ws));
    }
}

Server::Server(const asio::io_context::executor_type &ioc_executor,
               uint16_t port,
               std::shared_ptr<CollectionManager> collectionManager)
    : ioc_executor { ioc_executor },
      handler { ioc_executor, collectionManager },
      acceptor(ioc_executor, { tcp::v4(), port })
{
}