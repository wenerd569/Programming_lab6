
#include "frontend/commands/collection_interacts/show_command.hpp"
#include <vector>

Command ShowCommand::make(std::shared_ptr<IOManager> io,
                          std::shared_ptr<CollectionService> collectionService)
{
    return Command {
        " : вывести в стандартный поток вывода все элементы коллекции в строковом представлении",
        [=] (std::vector<std::string> &args) {
            if ( ! Command::getZeroArg(*io, args) ) {
                return;
            }
            Command::printPersonVector(*io, collectionService->getAllElement());
        }
    };
}
