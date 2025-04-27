
#include "frontend/commands/collection_interacts/add_command.hpp"
#include "frontend/forms/person_form.hpp"

Command AddCommand::make(std::shared_ptr<IOManager> io,
                         std::shared_ptr<CollectionService> collectionService)
{
    return Command { " {element} : добавить новый элемент в коллекцию",
                     [=] (std::vector<std::string> &args) {
                         if ( ! Command::getZeroArg(*io, args) ) {
                             return;
                         }
                         PersonPrecursor prePerson = PersonForm { io }.build();
                         Command::printStatus(*io, collectionService->add(prePerson));
                     } };
}
