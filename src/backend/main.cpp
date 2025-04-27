#include "backend/colection_manager.hpp"
#include "backend/server.hpp"
#include <boost/asio/io_context.hpp>
#include <iostream>
#include <memory>

int main (int argc, char *argv[])
{
    if ( argc != 2 ) {
        std::cerr
            << "Программа принимает на вход 1 аргумент, который должен содержать название файла коллекции"
            << std::endl;
        exit(1);
    }
    std::string fileName = argv[1];
    std::filesystem::path filePath = std::filesystem::path { fileName };
    std::shared_ptr<CollectionManager> collectionManager = std::make_shared<CollectionManager>(
        CollectionSerializer(filePath));

    asio::io_context ioc { 1 };
    Server server { ioc.get_executor(), 8081, collectionManager };
    ioc.run();
}