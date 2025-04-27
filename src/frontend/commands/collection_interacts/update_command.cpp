
#include "frontend/commands/collection_interacts/update_command.hpp"
#include "frontend/forms/person_form.hpp"

Command UpdateCommand::make(std::shared_ptr<IOManager> io,
                            std::shared_ptr<CollectionService> collectionService)
{
    return Command {
        " id {element} : обновить значение элемента коллекции, id которого равен заданному",
        [=] (std::vector<std::string> &args) {
            long id;
            if ( ! Command::getOneNumArg<long>(*io, args, id) ) {
                return;
            }

            auto rsp1 = collectionService->checkElement(id);

            if ( rsp1.getStatusCode() != Response<void>::OK ) {
                Command::printStatus(*io, std::move(rsp1));
                return;
            }
            PersonPrecursor prePerson = PersonForm(io).build();
            Command::printStatus(*io, collectionService->update(id, prePerson));
        }
    };
}