#include "backend/id_manager.hpp"

IdManager::IdManager() : lastId { 0 } {};
IdManager::IdManager(long lastId) : lastId { lastId } {};

long IdManager::getNext()
{
    return ++lastId;
}

long IdManager::getLast()
{
    return lastId;
}