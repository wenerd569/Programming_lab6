#pragma once

#include "common/interface/person_collection_service.hpp"
#include "frontend/reqest_sender.hpp"
#include <boost/beast/websocket/stream.hpp>

class PersonCollectionClient : public CollectionService {
private:
    RequestSender requestSender;

public:
    PersonCollectionClient(websocket::stream<tcp::socket> ws);

    Response<void> save () override;
    Response<CollectionInfo> getInfo () override;
    Response<void> add (PersonPrecursor &prePerson) override;
    Response<void> remove (long id) override;
    Response<void> update (long id, PersonPrecursor &prePerson) override;
    Response<void> clear () override;
    Response<void> inseartAt (size_t index, PersonPrecursor &prePerson) override;
    Response<void> addIfMax (PersonPrecursor &prePerson) override;
    Response<void> addIfMin (PersonPrecursor &prePerson) override;
    Response<void> checkElement (long id) override;
    Response<std::vector<Person>> getAllElement () override;
    Response<std::vector<Person>> getHeightLessElement (double height) override;
    Response<std::map<std::string, int>> groupCountingByName () override;
    Response<std::map<long, Country>> getFieldAscendingNationality () override;
};