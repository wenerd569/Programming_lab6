#pragma once

#include "common/structures/person_precursor.hpp"
#include <chrono>

struct Person : public PersonPrecursor {
    long id;                                   //>0, uniq, auto
    std::chrono::year_month_day creationDate;  // auto

public:
    Person(long id,
           std::string name,
           Coordinate coordinate,
           std::chrono::year_month_day creationDate,
           double height,
           std::optional<Color> eyeColor,
           Color hairColor,
           Country nationality,
           std::optional<Location> location)
        : PersonPrecursor { name, coordinate, height, eyeColor, hairColor, nationality, location },
          id { id },
          creationDate { creationDate }
    {
    }

    Person(PersonPrecursor prePerson, long id, std::chrono::year_month_day creationDate)
        : PersonPrecursor { prePerson }, id { id }, creationDate { creationDate } {};

    Person() {};
};