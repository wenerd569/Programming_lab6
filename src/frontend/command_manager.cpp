#include <memory>
#include <sstream>
#include <string>

#include "frontend/command_manager.hpp"

CommandManager::CommandManager() : commands {} {};

bool CommandManager::execute(std::string &line)
{
    char delimiter = ' ';
    std::stringstream ss { line };

    std::string command;
    std::getline(ss, command, delimiter);
    if ( commands.contains(command) ) {
        std::vector<std::string> args;
        std::string item;
        while ( std::getline(ss, item, delimiter) ) {
            args.push_back(item);
        }
        commands[command].execute(args);
        return true;
    } else {
        return false;
    }
}

void CommandManager::addCommand(Command command, std::string commandName)
{
    commands.insert({ std::move(commandName), std::move(command) });
}

const std::unordered_map<std::string, Command> &CommandManager::getCommands()
{
    return commands;
}