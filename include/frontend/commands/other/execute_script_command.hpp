
#include "frontend/commands/command.hpp"
#include <string>
#include <vector>

/**
 * @brief execute_script file_name : считать и исполнить скрипт из указанного файла. В скрипте
 * содержатся команды в таком же виде, в котором их вводит пользователь в интерактивном режиме.
 *
 */
class ExecuteScriptCommand {
public:
    static Command make (std::shared_ptr<IOManager> ioInterface);
};