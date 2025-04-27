
#include "frontend/commands/other/execute_script_command.hpp"
#include <ios>
#include <memory>

Command ExecuteScriptCommand::make(std::shared_ptr<IOManager> io)
{
    return Command {
        " file_name : считать и исполнить скрипт из указанного файла. В скрипте содержатся команды в таком же виде, в котором их вводит пользователь в интерактивном режиме.",
        [=] (std::vector<std::string> &args) {
            std::string filePath;
            if ( ! Command::getOneStringArg(*io, args, filePath) ) {
                return;
            }
            try {
                io->openNewReader(Reader::makeFileReader(filePath));
            } catch ( std::ios_base::failure e ) {
                io->writeError(e.what());
                io->write("\n");
            }
        }
    };
}
