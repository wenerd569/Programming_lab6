#include "frontend/commands/command.hpp"
#include <frontend/command_manager.hpp>
#include <string>
#include <unordered_map>

/**
 * @brief help : вывести справку по доступным командам
 *
 */
class HelpCommand {
public:
    static Command make (std::shared_ptr<IOManager> ioInterface,
                         const std::unordered_map<std::string, Command> &commands);
};