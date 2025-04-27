
#include "frontend/commands/command.hpp"
#include <cmath>
#include <format>
#include <magic_enum/magic_enum.hpp>
#include <string>
#include <utility>
#include <vector>

bool Command::getOneStringArg(IOManager &io, std::vector<std::string> &args, std::string &res)
{
    if ( args.size() != 1 ) {
        io.writeError("Данная функция принимает один строковый аргумент");
        return false;
    }
    res = args[0];
    return true;
}

bool Command::getZeroArg(IOManager &io, std::vector<std::string> &args)
{
    if ( args.size() != 0 ) {
        io.writeError("Данная функция не принимает аргументов");
        return false;
    }
    return true;
}

void Command::printPersonVector(IOManager &io, Response<std::vector<Person>> response)
{
    if ( response.getStatusCode() == Response<std::vector<Person>>::OK ) {
        io.write("Список персон:\n");
        for ( Person person : response.getData() ) {
            io.write(toString(person) + '\n');
        }
    } else {
        printStatus(io, std::move(response));
    }
}

std::string Command::toString(Person p)
{
    std::string coordinate = std::format("x: {}, y: {}", p.coordinate.x, p.coordinate.y);
    std::string location = "";
    if ( p.location.has_value() ) {
        location = std::format("x: {}, y: {}, z: {}", p.location->x, p.location->y, p.location->z);
    }
    std::string eyeColor = "none";
    if ( p.eyeColor.has_value() ) {
        eyeColor = magic_enum::enum_name(p.eyeColor.value());
    }
    std::string hairColor = (std::string)magic_enum::enum_name(p.hairColor);
    std::string nationality = (std::string)magic_enum::enum_name(p.nationality);

    std::string res = std::format(
        R"(id: {}
creationDate: {}
name: {}
coordinate: ({})
height: {}
eyeColor: {}
hairVolor: {}
nationality: {}
location : ({})
)",
        p.id, p.creationDate, p.name, coordinate, p.height, eyeColor,
        magic_enum::enum_name(p.hairColor), magic_enum::enum_name(p.nationality), location);
    return res;
}

std::string Command::toString(CollectionInfo info)
{
    std::string res = std::format(
        R"(initialDate: {}
lastId: {}
size: {}
type: {}
)",
        std::format("{:%Y-%m-%d}", info.initialDate), info.lastId, info.size, info.type);
    return res;
}