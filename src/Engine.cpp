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
    const ComponentSignature& signature = this->_entityManager->getSignature(id);

    this->_componentManager->onEntityDestroyed(id, signature);
    this->_entityManager->destroyEntity(id);
    this->_systemManager->onEntityDestroyed(id, signature);
}

void Engine::tick()
{
    this->_systemManager->run(this->_componentManager.get());
}
