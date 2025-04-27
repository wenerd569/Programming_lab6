
#include "common/interface/person_collection_service.hpp"
#include "frontend/commands/command.hpp"
#include <string>
#include <vector>

/**
 * @brief group_counting_by_name : сгруппировать элементы коллекции по значению поля name, вывести
 * количество элементов в каждой группе
 *
 */
class GroupCountingByNameCommand {
public:
    static Command make (std::shared_ptr<IOManager> ioInterface,
                         std::shared_ptr<CollectionService> collectionService);
};