

#include "common/interface/person_collection_service.hpp"
#include "frontend/commands/command.hpp"

/**
 * @brief add_if_max {element} : добавить новый элемент в коллекцию, если его значение превышает
 * значение наибольшего элемента этой коллекции
 *
 */
class AddIfMaxCommand {
public:
    static Command make (std::shared_ptr<IOManager> ioInterface,
                         std::shared_ptr<CollectionService> collectionService);
};