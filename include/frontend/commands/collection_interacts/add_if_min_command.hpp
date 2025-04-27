

#include "common/interface/person_collection_service.hpp"
#include "frontend/commands/command.hpp"

/**
 * @brief add_if_min {element} : добавить новый элемент в коллекцию, если его значение меньше, чем у
 * наименьшего элемента этой коллекции
 *
 */
class AddIfMinCommand {
public:
    static Command make (std::shared_ptr<IOManager> ioInterface,
                         std::shared_ptr<CollectionService> collectionService);
};