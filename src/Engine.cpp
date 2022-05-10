#include "../headers/Engine.hpp"
#include <iostream>

constexpr double STANDARD_FRAMERATE = 60;
constexpr double EXPECTED_MAX_DELTA = 0.1;
constexpr int MAX_LATE_FIXED_UPDATE_FRAME_COUNT = 2;

using namespace GameEngine;

Engine::Engine(double frameRate) : _frameRate(frameRate), _clock(Clock()),
    _maxDelta(EXPECTED_MAX_DELTA / (frameRate / STANDARD_FRAMERATE)), _frameDuration(1.0 / frameRate) {
    this->_componentManager = std::make_unique<ComponentManager>();
    this->_entityManager = std::make_unique<EntityManager>();
    this->_systemManager = std::make_unique<SystemManager>();
}

EntityId Engine::createEntity() {
    return this->_entityManager->createEntity();
}

void Engine::destroyEntity(const EntityId &id) {
    this->_entityManager->destroyEntity(id);
    this->_componentManager->onEntityDestroyed(id);
}

void Engine::tick() {
    _clock.update();

    double deltaTime = _clock.deltaTime;

    // tout lag est maximise 100 ms (1/10 de seconde)
    // cela permet d'eviter de faire sauter le moteur en cas de breakpoint ou lag enorme
    // alternativement on peut appliquer une correction en extrapolant a partir du temps ecoule
    if(deltaTime > _maxDelta)
        deltaTime = _maxDelta;

    // todo systems update

    _clock.fixedDeltaTime += _clock.deltaTime;
    double accumulatedTime = _clock.fixedDeltaTime;
    int loops = MAX_LATE_FIXED_UPDATE_FRAME_COUNT;
    while((accumulatedTime > _frameDuration) && loops > 0){
        accumulatedTime -= _frameDuration;

        // todo systems fixedUpdate

        --loops;
    }
}
