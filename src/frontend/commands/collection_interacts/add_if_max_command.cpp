
#include "frontend/commands/collection_interacts/add_if_max_command.hpp"
#include "frontend/forms/person_form.hpp"

Command AddIfMaxCommand::make(std::shared_ptr<IOManager> io,
                              std::shared_ptr<CollectionService> collectionService)
{
    return Command(
        " {element} : добавить новый элемент в коллекцию, если его значение превышает значение наибольшего элемента этой коллекции",
        [=] (std::vector<std::string> &args) {
            if ( ! Command::getZeroArg(*io, args) ) {
                return;
            }
            PersonPrecursor prePerson = PersonForm(io).build();
            Command::printStatus(*io, collectionService->addIfMax(prePerson));
        });
};
