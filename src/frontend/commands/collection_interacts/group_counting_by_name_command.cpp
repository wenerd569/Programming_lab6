
#include "frontend/commands/collection_interacts/group_counting_by_name_command.hpp"
#include <string>
#include <utility>
#include <vector>

Command GroupCountingByNameCommand::make(std::shared_ptr<IOManager> io,
                                         std::shared_ptr<CollectionService> collectionService)
{
    return Command {
        " : сгруппировать элементы коллекции по значению поля name, вывести количество элементов в каждой группе",
        [=] (std::vector<std::string> &args) {
            if ( ! Command::getZeroArg(*io, args) ) {
                return;
            }
            auto rsp = collectionService->groupCountingByName();
            if ( rsp.getStatusCode() == Response<std::map<std::string, int>>::OK ) {
                for ( std::pair<std::string, int> line : rsp.getData() ) {
                    io->write(line.first + " : " + std::to_string(line.second) + "\n");
                }
            } else {
                Command::printStatus(*io, std::move(rsp));
            }
        }

    };
}