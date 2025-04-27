
#include "common/interface/person_collection_service.hpp"
#include "frontend/commands/command.hpp"
#include <string>
#include <vector>

/**
 * @brief print_field_ascending_nationality : вывести значения поля nationality всех элементов в
 * порядке возрастания Пока не реализованно
 */
class PrintFieldAscengroupCountingByNamedingNationalityCommand {
public:
    static Command make (std::shared_ptr<IOManager> ioInterface,
                         std::shared_ptr<CollectionService> collectionService);
};