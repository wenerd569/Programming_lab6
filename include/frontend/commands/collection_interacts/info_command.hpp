
#include "common/interface/person_collection_service.hpp"
#include "frontend/commands/command.hpp"
#include <string>
#include <vector>

/**
 * @brief info : вывести в стандартный поток вывода информацию о коллекции (тип, дата инициализации,
 * количество элементов и т.д.)
 *
 */
class InfoCommand {
public:
    static Command make (std::shared_ptr<IOManager> ioInterface,
                         std::shared_ptr<CollectionService> collectionService);
};