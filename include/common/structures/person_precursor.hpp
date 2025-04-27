#pragma once

#include "common/structures/color.hpp"
#include "common/structures/coordinate.hpp"
#include "common/structures/country.hpp"
#include "common/structures/location.hpp"
#include <optional>
#include <string>

/**
 * @brief Данные от Person которые нужно получать на клиенте
 *
 */
struct PersonPrecursor {
    std::string name;                  //
    Coordinate coordinate;             //
    double height;                     //>0
    std::optional<Color> eyeColor;     // null
    Color hairColor;                   //
    Country nationality;               //
    std::optional<Location> location;  // null

    PersonPrecursor(std::string name,
                    Coordinate coordinate,
                    double height,
                    std::optional<Color> eyeColor,
                    Color hairColor,
                    Country nationality,
                    std::optional<Location> location)
        : name { name },
          coordinate { coordinate },
          height { height },
          eyeColor { eyeColor },
          hairColor { hairColor },
          nationality { nationality },
          location { location } {};

    PersonPrecursor() {};
};