#include "common/from_to_json.hpp"
#include <fstream>
#include <ios>
#include <iostream>
#include <nlohmann/json.hpp>
#include <nlohmann/json_fwd.hpp>
#include <ostream>
#include <utility>

#include "backend/collection_serializer.hpp"

CollectionSerializer::CollectionSerializer(std::filesystem::path filePath)
    : filePath { std::move(filePath) }
{
}

void CollectionSerializer::serialize(std::vector<Person> &persons, CollectionInfo &info)
{
    std::ofstream file = std::ofstream(filePath, std::ios::out | std::ios::trunc);
    if ( ! file ) {
        throw std::ios_base::failure("Не удаётся открыть файл колекции");
    }

    json res = json { { "collection", persons }, { "collectionInfo", info } };
    file << res.dump() << std::endl;
    file.close();
}

std::pair<std::vector<Person>, std::optional<CollectionInfo>> CollectionSerializer::deserialize()
{
    std::ifstream file = std::ifstream(filePath, std::ios::in);
    if ( ! file ) {
        throw std::ios_base::failure("Не удаётся открыть файл колекции");
    }
    json data;
    data = json::parse(file);
    file.close();

    std::optional<CollectionInfo> nullInfo;

    if ( data.contains("collectionInfo") ) {
        CollectionInfo info = CollectionInfo();
        data.at("collectionInfo").get_to(info);
        nullInfo = info;
    } else {
        nullInfo = std::optional<CollectionInfo>();
    }

    std::vector<Person> persons = std::vector<Person>();
    if ( data.contains("collection") ) {
        for ( json j : data.at("collection") ) {
            Person p = j;
            persons.push_back(p);
        }
    }

    return std::pair<std::vector<Person>, std::optional<CollectionInfo>>(persons, nullInfo);
}
