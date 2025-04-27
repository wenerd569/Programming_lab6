
#include "common/interface/person_collection_service.hpp"
#include "frontend/commands/command.hpp"
#include <string>
#include <vector>

/**
 * @brief remove_by_id id : удалить элемент из коллекции по его id
 *
 */
class RemoveCommand {
public:
    static Command make (std::shared_ptr<IOManager> ioInterface,
                         std::shared_ptr<CollectionService> collectionService);
};