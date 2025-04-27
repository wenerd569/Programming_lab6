
#include "common/interface/person_collection_service.hpp"
#include "frontend/command_manager.hpp"
#include "frontend/person_collection_client.hpp"
#include <boost/asio/io_context.hpp>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <filesystem>
#include <memory>
#include <nlohmann/detail/input/input_adapters.hpp>

/**
 * @brief Класс программы
 */
class Program {
    asio::io_context::executor_type &ioc_executor;
    std::shared_ptr<CommandManager> commandManager;
    std::shared_ptr<CollectionService> collectionManager;
    std::shared_ptr<IOManager> io;

public:
    /**
     * @brief Конструктор программы вызывает инициализаторы всех полей класса
     * @param filePath
     */
    Program(asio::io_context::executor_type &ioc_executor);
    virtual ~Program() = default;
    /**
     * @brief Начинает бесконечный цикл обработки команд
     *
     */
    virtual void start ();
};
