#include "../headers/EntityManager.h"

using namespace GameEngine;

EntityManager::EntityManager()
{
    for (EntityId i = 0; i < MAX_ENTITIES; ++i)
        this->_availableEntities.emplace(i);
}

EntityId EntityManager::createEntity()
{
    EntityId id = this->_availableEntities.front();

    this->_availableEntities.pop();
    return id;
}

void EntityManager::destroyEntity(const EntityId& id)
{
    this->_availableEntities.push(id);
}
