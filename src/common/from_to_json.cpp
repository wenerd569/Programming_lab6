#include <chrono>
#include <format>
#include <nlohmann/adl_serializer.hpp>
#include <optional>
#include <string>

#include "common/from_to_json.hpp"

using json = nlohmann::json;
using namespace std::chrono;

void to_json (json &j, const Coordinate &p)
{
    j = json { { "x", p.x }, { "y", p.y } };
}

void from_json (const json &j, Coordinate &p)
{
    j.at("x").get_to(p.x);
    j.at("y").get_to(p.y);
}

void to_json (json &j, const Location &p)
{
    j = json { { "x", p.x }, { "y", p.y }, { "z", p.z } };
}

void from_json (const json &j, Location &p)
{
    j.at("x").get_to(p.x);
    j.at("y").get_to(p.y);
    j.at("z").get_to(p.z);
}

void to_json (json &j, const PersonPrecursor &p)
{
    j = json { { "name", p.name },
               { "coordinate", p.coordinate },
               { "height", p.height },
               { "hairColor", p.hairColor },
               { "nationality", p.nationality } };
    if ( p.eyeColor.has_value() ) {
        j["eyeColor"] = p.eyeColor.value();
    }
    if ( p.location.has_value() ) {
        j["location"] = p.location.value();
    }
}

void from_json (const json &j, PersonPrecursor &p)
{
    j.at("name").get_to(p.name);
    from_json(j.at("coordinate"), p.coordinate);
    j.at("height").get_to(p.height);
    j.at("hairColor").get_to(p.hairColor);
    j.at("nationality").get_to(p.nationality);

    if ( j.contains("eyeColor") ) {
        p.eyeColor = j.at("eyeColor").get<Color>();
    } else {
        p.eyeColor = std::optional<Color>();
    }

    if ( j.contains("location") ) {
        Location l = Location();
        from_json(j.at("location"), l);
        p.location = std::optional<Location>(l);
    } else {
        p.location = std::optional<Location>();
    }
}

void to_json (nlohmann::json &j, const Person &p)
{
    j = (PersonPrecursor)p;
    j["id"] = p.id;
    j["creationDate"] = p.creationDate;
}

void from_json (const nlohmann::json &j, Person &p)
{
    PersonPrecursor prePerson = PersonPrecursor {};
    from_json(j, prePerson);
    long id;
    year_month_day creationDate;
    j.at("id").get_to(id);
    j.at("creationDate").get_to(creationDate);
    p = Person { prePerson, id, creationDate };
}

void to_json (nlohmann::json &j, const CollectionInfo &p)
{
    j = json { { "initialDate", p.initialDate },
               { "lastId", p.lastId },
               { "size", p.size },
               { "type", p.type } };
}

void from_json (const nlohmann::json &j, CollectionInfo &p)
{
    j.at("initialDate").get_to(p.initialDate);
    j.at("lastId").get_to(p.lastId);
    j.at("size").get_to(p.size);
    j.at("type").get_to(p.type);
}

void nlohmann::adl_serializer<year_month_day>::to_json(json &j,
                                                       const std::chrono::year_month_day &p)
{
    j = std::format("{:%Y-%m-%d}", p);
}

void nlohmann::adl_serializer<year_month_day>::from_json(const json &j,
                                                         std::chrono::year_month_day &p)
{
    std::string date_str = j.get<std::string>();
    int y;
    unsigned m, d;
    char d1, d2;
    std::istringstream iss(date_str);
    if ( ! (iss >> y >> d1 >> m >> d2 >> d) || d1 != '-' || d2 != '-' ) {
        throw std::invalid_argument("Invalid date format. Expected 'YYYY-MM-DD'.");
    }

    p = year { y } / month { m } / day { d };

    if ( ! p.ok() ) {
        throw std::invalid_argument("Invalid date value.");
    }
}