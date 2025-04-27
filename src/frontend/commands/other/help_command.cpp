
#include "frontend/commands/other/help_command.hpp"

Command HelpCommand::make(std::shared_ptr<IOManager> io,
                          const std::unordered_map<std::string, Command> &commands)
{
    return Command { " : вывести справку по доступным командам",
                     [=, &commands] (std::vector<std::string> &args) {
                         if ( ! Command::getZeroArg(*io, args) ) {
                             return;
                         }
                         for ( auto &element : commands ) {
                             io->write(element.first + element.second.description + '\n');
                         }
                     } };
};