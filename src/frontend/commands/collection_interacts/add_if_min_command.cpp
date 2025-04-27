
#include "frontend/commands/collection_interacts/add_if_min_command.hpp"
#include "frontend/forms/person_form.hpp"

Command AddIfMinCommand::make(std::shared_ptr<IOManager> io,
                              std::shared_ptr<CollectionService> collectionService)
{
    return Command {
        " {element} : добавить новый элемент в коллекцию, если его значение меньше, чем у наименьшего элемента этой коллекции",
        [=] (std::vector<std::string> &args) {
            if ( ! Command::getZeroArg(*io, args) ) {
                return;
            }
            PersonPrecursor prePerson = PersonForm(io).build();
            Command::printStatus(*io, collectionService->addIfMin(prePerson));
        }

    };
}