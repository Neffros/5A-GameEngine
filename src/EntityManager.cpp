#include "../headers/EntityManager.h"

using namespace GameEngine;

EntityManager::EntityManager()
{
    for (EntityId i = 0; i < MAX_ENTITIES; ++i)
        this->_availableEntities.emplace(i);
}

EntityId EntityManager::createEntity(const std::string& tag)
{
    EntityId id = this->_availableEntities.front();
    this->_tagToEntities[tag].push_back(id);
    this->_entityToTag[id] = tag;
    this->_availableEntities.pop();
    return id;
}

void EntityManager::destroyEntity(const EntityId& id)
{
    this->_availableEntities.push(id);
    this->_entityToSignature[id].reset();
    std::vector<EntityId>& entities = this->_tagToEntities[_entityToTag[id]];
    for (auto it = entities.begin(); it != entities.end(); ++it)
    {
        if (*it == id)
        {
            entities.erase(it);
            break;
        }
    }
}

ComponentSignature EntityManager::getSignature(const EntityId& id) const
{
    return this->_entityToSignature[id];
}

void EntityManager::setSignature(const EntityId& id, ComponentSignature signature)
{
    this->_entityToSignature[id] = signature;
}

std::vector<EntityId> EntityManager::getEntitiesByTag(std::string &tag) {

    std::vector<EntityId> entities;
    for(auto & _tagToEntity : _tagToEntities) {
        if(_tagToEntity.first == tag)
        {
            entities = _tagToEntity.second;
        }
    }
    return entities;
}

