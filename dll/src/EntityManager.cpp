#include "../headers/EntityManager.h"
using namespace GameEngine;


EntityManager::EntityManager() {
    for (int i = 0; i < MAX_ENTITIES; ++i) {
        availableEntities.emplace(i);
    }
}

EntityID EntityManager::createEntity() {
    EntityID id = availableEntities.front();
    availableEntities.pop();
    return id;
}

void EntityManager::destroyEntity(EntityID id) {
    availableEntities.push(id);
}