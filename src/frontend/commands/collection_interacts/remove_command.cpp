
#include "frontend/commands/collection_interacts/remove_command.hpp"

Command RemoveCommand::make(std::shared_ptr<IOManager> io,
                            std::shared_ptr<CollectionService> collectionService)
{
    return Command { " id : удалить элемент из коллекции по его id",
                     [=] (std::vector<std::string> &args) {
                         long id;
                         if ( ! Command::getOneNumArg<long>(*io, args, id) ) {
                             return;
                         }
                         Command::printStatus(*io, collectionService->remove(id));
                     }

    };
}