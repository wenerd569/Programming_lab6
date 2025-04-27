

#include "frontend/commands/collection_interacts/filter_less_than_height_command.hpp"

Command FilterLessThanHeightCommand::make(std::shared_ptr<IOManager> io,
                                          std::shared_ptr<CollectionService> collectionService)
{
    return Command {
        " height : вывести элементы, значение поля height которых меньше заданного",
        [=] (std::vector<std::string> &args) {
            double height;
            if ( ! Command::getOneNumArg<double>(*io, args, height) ) {
                return;
            }
            Command::printPersonVector(*io, collectionService->getHeightLessElement(height));
        }

    };
}
