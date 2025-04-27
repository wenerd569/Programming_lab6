
#include "common/interface/person_collection_service.hpp"
#include "frontend/commands/command.hpp"
#include <string>
#include <vector>

/**
 * @brief insert_at index {element} : добавить новый элемент в заданную позицию
 * Перед запросом элемента провяет не выходит ли индекс за границы колекции
 */
class InseartCommand {
public:
    static Command make (std::shared_ptr<IOManager> ioInterface,
                         std::shared_ptr<CollectionService> collectionService);
};