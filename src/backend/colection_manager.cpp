#include "common/exeptions/program_terminate_exeption.hpp"
#include "common/validators.hpp"
#include <algorithm>
#include <backend/colection_manager.hpp>
#include <cmath>
#include <iostream>
#include <limits>
#include <nlohmann/json_fwd.hpp>
#include <utility>
#include <vector>

const long getLastId (std::vector<Person> persons)
{
    long res = 0;
    for ( auto p : persons ) {
        res = std::max(res, p.id);
    }
    return res;
}

CollectionManager::CollectionManager(CollectionSerializer _collectionSerializer)
    : collectionSerializer { std::move(_collectionSerializer) }
{
    std::optional<CollectionInfo> nullInfo;
    auto tmp = collectionSerializer.deserialize();
    persons = std::move(tmp.first);
    nullInfo = std::move(tmp.second);

    if ( nullInfo.has_value() ) {
        dateManager = DateManager { nullInfo->initialDate };
        idManager = IdManager(std::max(nullInfo->lastId, getLastId(persons)));
        type = std::move(nullInfo->type);
    } else {
        idManager = IdManager { getLastId(persons) };
        dateManager = DateManager {};
        type = "Person";
    }
};

Person CollectionManager::createPerson(PersonPrecursor &prePerson)
{
    return Person(prePerson, idManager.getNext(), dateManager.getCurrentDate());
}

CollectionInfo CollectionManager::configureInfo()
{
    return CollectionInfo(type, dateManager.getInitialDate(), persons.size(), idManager.getLast());
}

Reqest<CollectionInfo> CollectionManager::getInfo()
{
    return Reqest<CollectionInfo>::success(std::move(configureInfo()));
}

Response<void> CollectionManager::add(PersonPrecursor &prePerson)
{
    if ( Validator<PersonPrecursor>::validate(prePerson) == ValidatorStatusCode::Error ) {
        return Response<void>::failure(Response<void>::FAIL);
    }
    persons.push_back(createPerson(prePerson));
    return Response<void>::success();
}

Response<void> CollectionManager::remove(long id)
{
    for ( size_t i = 0; i < persons.size(); ++i ) {
        if ( persons[i].id == id ) {
            persons.erase(i + persons.begin());
            if ( id == idManager.getLast() ) {
                idManager = IdManager(getLastId(persons));
            }
            return Response<void>::success();
        }
    }
    return Response<void>::failure(Response<void>::ELEMENT_NOT_FOUND);
}

Response<void> CollectionManager::update(long id, PersonPrecursor &prePerson)
{
    if ( Validator<PersonPrecursor>::validate(prePerson) == ValidatorStatusCode::Error ) {
        return Response<void>::failure(Response<void>::FAIL);
    }
    for ( size_t i = 0; i < persons.size(); ++i ) {
        if ( persons[i].id == id ) {
            persons[i] = Person(prePerson, id, persons[i].creationDate);
            return Response<void>::success();
        }
    }
    return Response<void>::failure(Response<void>::ELEMENT_NOT_FOUND);
}

Response<void> CollectionManager::checkElement(long id)
{
    for ( size_t i = 0; i < persons.size(); ++i ) {
        if ( persons[i].id == id ) {
            return Response<void>::success();
        }
    }
    return Response<void>::failure(Response<void>::ELEMENT_NOT_FOUND);
}

Response<void> CollectionManager::clear()
{
    persons.clear();
    idManager = IdManager(getLastId(persons));
    return Response<void>::success();
}

Response<void> CollectionManager::save()
{
    CollectionInfo info = configureInfo();
    try {
        collectionSerializer.serialize(persons, info);
        return Response<void>::success();
    } catch ( std::ios_base::failure e ) {
        return Response<void>::failure(Response<void>::CANT_SAVE_DATA);
    }
}

Response<void> CollectionManager::inseartAt(size_t index, PersonPrecursor &prePerson)
{
    if ( index > persons.size() ) {
        return Response<void>::failure(Response<void>::INDEX_OUT_OF_RANGE);
    }
    persons.insert(index + persons.begin(), createPerson(prePerson));
    return Response<void>::success();
}

Response<void> CollectionManager::addIfMax(PersonPrecursor &prePerson)
{
    if ( Validator<PersonPrecursor>::validate(prePerson) == ValidatorStatusCode::Error ) {
        return Response<void>::failure(Response<void>::FAIL);
    }
    double max = -1;
    for ( size_t i = 0; i < persons.size(); ++i ) {
        max = std::max(persons[i].height, max);
    }

    if ( max < prePerson.height ) {
        add(prePerson);
        return Response<void>::success();
    }
    return Response<void>::failure(Response<void>::FAIL);
}

Response<void> CollectionManager::addIfMin(PersonPrecursor &prePerson)
{
    if ( Validator<PersonPrecursor>::validate(prePerson) == ValidatorStatusCode::Error ) {
        return Response<void>::failure(Response<void>::FAIL);
    }
    double min = std::numeric_limits<double>::max();
    for ( size_t i = 0; i < persons.size(); ++i ) {
        min = std::min(persons[i].height, min);
    }

    if ( min > prePerson.height ) {
        add(prePerson);
        return Response<void>::success();
    }
    return Response<void>::failure(Response<void>::FAIL);
}

Reqest<std::vector<Person>> CollectionManager::getAllElement()
{
    if ( persons.empty() ) {
        return Reqest<std::vector<Person>>::failure(Reqest<std::vector<Person>>::NULL_RESULT);
    }
    return Reqest<std::vector<Person>>::success(persons);
}

Reqest<std::vector<Person>> CollectionManager::getHeightLessElement(double height)
{
    std::vector<Person> res = std::vector<Person>();
    for ( size_t i = 0; i < persons.size(); ++i ) {
        if ( persons[i].height < height ) {
            res.push_back(persons[i]);
        }
    }
    if ( res.empty() ) {
        return Reqest<std::vector<Person>>::failure(Reqest<std::vector<Person>>::NULL_RESULT);
    }
    return Reqest<std::vector<Person>>::success(res);
}

Reqest<std::map<std::string, int>> CollectionManager::groupCountingByName()
{
    std::map<std::string, int> res = std::map<std::string, int>();

    for ( size_t i = 0; i < persons.size(); ++i ) {
        if ( res.contains(persons[i].name) ) {
            res[persons[i].name] += 1;
        } else {
            res[persons[i].name] = 1;
        }
    }
    if ( res.empty() ) {
        return Reqest<std::map<std::string, int>>::failure(
            Reqest<std::map<std::string, int>>::NULL_RESULT);
    }
    return Reqest<std::map<std::string, int>>::success(res);
}

Reqest<std::map<long, Country>> CollectionManager::getFieldAscendingNationality()
{
    std::map<long, Country> res = std::map<long, Country>();

    for ( int i = 0; i < persons.size(); i++ ) {
        res[persons[i].id] = persons[i].nationality;
    }
    return Reqest<std::map<long, Country>>::success(res);
}