
#include "frontend/commands/collection_interacts/inseart_command.hpp"
#include <cstddef>
#include <frontend/forms/person_form.hpp>

Command InseartCommand::make(std::shared_ptr<IOManager> io,
                             std::shared_ptr<CollectionService> collectionService)
{
    return Command { " index {element} : добавить новый элемент в заданную позицию",
                     [=] (std::vector<std::string> &args) {
                         size_t index;
                         if ( ! Command::getOneNumArg<size_t>(*io, args, index) ) {
                             return;
                         }
                         auto rsp1 = collectionService->getInfo();
                         if ( rsp1.getStatusCode() != Response<CollectionInfo>::OK ) {
                             Command::printStatus(*io, std::move(rsp1));
                             return;
                         }
                         size_t collect_size = rsp1.getData().size;

                         if ( collect_size < index ) {
                             io->writeError(
                                 "В коллекции меньше элементов, чем придоставленный вами индекс\n");
                             return;
                         }

                         PersonPrecursor prePerson = PersonForm { io }.build();

                         Command::printStatus(*io, collectionService->inseartAt(index, prePerson));
                     } };
}