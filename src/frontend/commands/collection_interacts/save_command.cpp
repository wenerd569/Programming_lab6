
#include "frontend/commands/collection_interacts/save_command.hpp"

Command SaveCommand::make(std::shared_ptr<IOManager> io,
                          std::shared_ptr<CollectionService> collectionService)
{
    return Command { " : сохранить коллекцию в файл", [=] (std::vector<std::string> &args) {
                        if ( ! Command::getZeroArg(*io, args) ) {
                            return;
                        }
                        Command::printStatus(*io, collectionService->save());
                    } };
}
