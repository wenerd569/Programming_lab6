#pragma once

#include "common/response.hpp"
#include "common/structures/collection_info.hpp"
#include "common/structures/person.hpp"
#include <map>

class CollectionService {
public:
    virtual Response<void> save () = 0;
    virtual Response<CollectionInfo> getInfo () = 0;
    virtual Response<void> add (PersonPrecursor &prePerson) = 0;
    virtual Response<void> remove (long id) = 0;
    virtual Response<void> update (long id, PersonPrecursor &prePerson) = 0;
    virtual Response<void> clear () = 0;
    virtual Response<void> inseartAt (size_t index, PersonPrecursor &prePerson) = 0;
    virtual Response<void> addIfMax (PersonPrecursor &prePerson) = 0;
    virtual Response<void> addIfMin (PersonPrecursor &prePerson) = 0;
    virtual Response<void> checkElement (long id) = 0;
    virtual Response<std::vector<Person>> getAllElement () = 0;
    virtual Response<std::vector<Person>> getHeightLessElement (double height) = 0;
    virtual Response<std::map<std::string, int>> groupCountingByName () = 0;
    virtual Response<std::map<long, Country>> getFieldAscendingNationality () = 0;

    virtual ~CollectionService() = default;
};