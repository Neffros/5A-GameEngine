#include "../headers/Engine.hpp"

using namespace GameEngine;

Engine::Engine()
{
    this->_componentManager = std::make_unique<ComponentManager>();
    this->_entityManager = std::make_unique<EntityManager>();
    this->_systemManager = std::make_unique<SystemManager>();
}

EntityId Engine::createEntity()
{
    return this->_entityManager->createEntity();
}

void Engine::destroyEntity(const EntityId& id)
{
    this->_entityManager->destroyEntity(id);
    this->_componentManager->onEntityDestroyed(id);
}

void Engine::tick()
{

}

