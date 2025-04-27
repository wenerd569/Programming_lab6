
#include "frontend/commands/collection_interacts/info_command.hpp"
#include <utility>

Command InfoCommand::make(std::shared_ptr<IOManager> io,
                          std::shared_ptr<CollectionService> collectionService)
{
    return Command {
        " : вывести в стандартный поток вывода информацию о коллекции (тип, дата инициализации, количество элементов и т.д.)",
        [=] (std::vector<std::string> &args) {
            if ( ! Command::getZeroArg(*io, args) ) {
                return;
            }

            auto rsp = collectionService->getInfo();

            if ( rsp.getStatusCode() == Response<CollectionInfo>::OK ) {
                io->write(Command::toString(rsp.getData()) + '\n');
            } else {
                Command::printStatus(*io, std::move(rsp));
            }
        }
    };
}
