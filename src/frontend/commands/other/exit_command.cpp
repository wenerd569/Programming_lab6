
#include "frontend/commands/other/exit_command.hpp"
#include "common/exeptions/program_terminate_exeption.hpp"

Command ExitCommand::make(std::shared_ptr<IOManager> io)
{
    return Command { " : завершить программу (без сохранения в файл)",
                     [=] (std::vector<std::string> &args) {
                         if ( ! Command::getZeroArg(*io, args) ) {
                             return;
                         }
                         throw ProgramTerminateException("Принудительный выход из программы");
                     } };
}