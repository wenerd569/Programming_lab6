

#include "common/interface/person_collection_service.hpp"
#include "frontend/commands/command.hpp"

/**
 * @brief add {element} : добавить новый элемент в коллекцию
 *
 */
class AddCommand {
public:
    static Command make (std::shared_ptr<IOManager> ioInterface,
                         std::shared_ptr<CollectionService> collectionService);
};