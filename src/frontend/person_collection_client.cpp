#include "frontend/person_collection_client.hpp"
#include <boost/beast/websocket/stream.hpp>

PersonCollectionClient::PersonCollectionClient(websocket::stream<tcp::socket> ws)
    : requestSender { std::move(ws) }
{
}

Response<void> PersonCollectionClient::save() { }

Response<CollectionInfo> PersonCollectionClient::getInfo() { }

Response<void> PersonCollectionClient::add(PersonPrecursor &prePerson) { }

Response<void> PersonCollectionClient::remove(long id) { }

Response<void> PersonCollectionClient::update(long id, PersonPrecursor &prePerson) { }

Response<void> PersonCollectionClient::clear() { }

Response<void> PersonCollectionClient::inseartAt(size_t index, PersonPrecursor &prePerson) { }

Response<void> PersonCollectionClient::addIfMax(PersonPrecursor &prePerson) { }

Response<void> PersonCollectionClient::addIfMin(PersonPrecursor &prePerson) { }

Response<void> PersonCollectionClient::checkElement(long id) { }

Response<std::vector<Person>> PersonCollectionClient::getAllElement() { }

Response<std::vector<Person>> PersonCollectionClient::getHeightLessElement(double height) { }

Response<std::map<std::string, int>> PersonCollectionClient::groupCountingByName() { }

Response<std::map<long, Country>> PersonCollectionClient::getFieldAscendingNationality() { }