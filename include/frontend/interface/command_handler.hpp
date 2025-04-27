#pragma once

#include "frontend/commands/command.hpp"
#include <memory>
#include <string>
#include <unordered_map>

class Command;

/**
 * @brief Интерфейс обработчика команд
 *
 */
class CommandHandler {
public:
    /**
     * @brief Выполнить команду по её названию
     * @param line через пробел должна содержать команду и её описание
     */
    virtual void execute (std::string &line) = 0;
    /**
     * @brief Добавить команду для обработки
     * Используется при инициализации класса
     * @param coomand
     * @param commandName
     */
    virtual void addCommand (std::unique_ptr<Command> coomand, std::string commandName) = 0;

    /**
     * @brief Получить список всех команд
     * Используется только командой help
     * @return const std::unordered_map<std::string, std::unique_ptr<Command>>&
     */
    virtual const std::unordered_map<std::string, std::unique_ptr<Command>> &getCommands () = 0;

    virtual ~CommandHandler() = default;
};
