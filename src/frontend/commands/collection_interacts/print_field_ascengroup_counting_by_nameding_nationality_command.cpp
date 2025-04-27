
#include "frontend/commands/collection_interacts/print_field_ascengroup_counting_by_nameding_nationality_command.hpp"
#include <magic_enum/magic_enum.hpp>
#include <string>

Command PrintFieldAscengroupCountingByNamedingNationalityCommand::make(
    std::shared_ptr<IOManager> io, std::shared_ptr<CollectionService> collectionService)
{
    return Command {
        " : вывести значения поля nationality всех элементов в порядке возрастания",
        [=] (std::vector<std::string> &args) {
            if ( ! Command::getZeroArg(*io, args) ) {
                return;
            }
            auto rsp = collectionService->getFieldAscendingNationality();
            if ( rsp.getStatusCode() == Response<std::map<long, Country>>::OK ) {
                for ( std::pair<long, Country> line : rsp.getData() ) {
                    std::string countryName = (std::string)magic_enum::enum_name(line.second);
                    io->write(std::to_string(line.first) + " : " + countryName + "\n");
                }
            } else {
                Command::printStatus(*io, std::move(rsp));
            }
        }

    };
}
