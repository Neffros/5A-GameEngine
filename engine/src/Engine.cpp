#include "Engine.h"

GameEngine::EntityId GameEngine::Engine::createEntity() {
    return entityManager.createEntity();
}

void GameEngine::Engine::destroyEntity(GameEngine::EntityId id) {
    entityManager.destroyEntity(id);
}

void GameEngine::Engine::addComponent(GameEngine::EntityId entityId, GameEngine::ComponentId componentId) {
    componentManager.addComponentToEntity(entityId, componentId);
}

template<typename TComponent>
TComponent GameEngine::Engine::getComponent(GameEngine::EntityId entityId) {
    return componentManager.getComponentOfEntity<TComponent>(entityId);;
}



template<typename TSystem>
void GameEngine::Engine::RegisterSystem() {
    RegisterSystem<TSystem>();
}

void GameEngine::Engine::tick() {
}

template<typename TComponent>
void GameEngine::Engine::registerComponent() {
    componentManager.registerComponent<TComponent>();
}

template<typename TComponent>
void GameEngine::Engine::removeComponent(GameEngine::EntityId entityId) {
    componentManager.removeComponentOfEntity<TComponent>(entityId);
}


