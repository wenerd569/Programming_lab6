
#include "frontend/commands/collection_interacts/clear_command.hpp"

Command ClearCommand::make(std::shared_ptr<IOManager> io,
                           std::shared_ptr<CollectionService> collectionService)
{
    return Command { " : очистить коллекцию", [=] (std::vector<std::string> &args) {
                        if ( ! Command::getZeroArg(*io, args) ) {
                            return;
                        }
                        Command::printStatus(*io, collectionService->clear());
                    } };
}
