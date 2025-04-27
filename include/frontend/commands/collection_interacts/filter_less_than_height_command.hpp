

#include "common/interface/person_collection_service.hpp"
#include "frontend/commands/command.hpp"

/**
 * @brief filter_less_than_height height : вывести элементы, значение поля height которых меньше
 * заданного
 *
 */
class FilterLessThanHeightCommand {
public:
    static Command make (std::shared_ptr<IOManager> ioInterface,
                         std::shared_ptr<CollectionService> collectionService);
};