#pragma once

#include "common/command_call_request.hpp"
#include "common/response.hpp"
#include "structures/collection_info.hpp"
#include "structures/person.hpp"
#include <chrono>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

void to_json (json &j, const Coordinate &p);
void from_json (const json &j, Coordinate &p);

void to_json (json &j, const Location &p);
void from_json (const json &j, Location &p);

void to_json (json &j, const PersonPrecursor &p);
void from_json (const json &j, PersonPrecursor &p);

void to_json (json &j, const std::chrono::year_month_day &p);
void from_json (const json &j, std::chrono::year_month_day &p);

void to_json (json &j, const Person &p);
void from_json (const json &j, Person &p);

void to_json (json &j, const CollectionInfo &p);
void from_json (const json &j, CollectionInfo &p);

NLOHMANN_JSON_SERIALIZE_ENUM(Country,
                             { { UNITED_KINGDOM, "UNITED_KINGDOM" },
                               { ITALY, "ITALY" },
                               { NORTH_KOREA, "NORTH_KOREA" } });

NLOHMANN_JSON_SERIALIZE_ENUM(Color,
                             { { RED, "RED" },
                               { BLUE, "BLUE" },
                               { YELLOW, "YELLOW" },
                               { WHITE, "WHITE" },
                               { GREEN, "GREEN" },
                               { BROWN, "BROWN" } });

namespace nlohmann {
    template<>
    struct adl_serializer<std::chrono::year_month_day> {
        static void to_json (json &j, const std::chrono::year_month_day &ymd);
        static void from_json (const json &j, std::chrono::year_month_day &ymd);
    };
}  // namespace nlohmann

NLOHMANN_JSON_SERIALIZE_ENUM(ResponseCode,
                             {
                                 { OK, "OK" },
                                 { NULL_RESULT, "NULL_RESULT" },
                                 { ELEMENT_NOT_FOUND, "ELEMENT_NOT_FOUND" },
                                 { CANT_SAVE_DATA, "CANT_SAVE_DATA" },
                                 { INDEX_OUT_OF_RANGE, "INDEX_OUT_OF_RANGE" },
                                 { FAIL, "FAIL" },
                                 { SERVER_NOT_RESPONCE, "SERVER_NOT_RESPONCE" },
                             });
