#include "../headers/Engine.hpp"
#include <iostream>

constexpr double STANDARD_FRAMERATE = 60;
constexpr double EXPECTED_MAX_DELTA = 0.1;
constexpr int MAX_LATE_FIXED_UPDATE_FRAME_COUNT = 2;

using namespace GameEngine;

Engine::Engine(double frameRate) : _clock(Clock()), _frameRate(frameRate), _frameDuration(1.0 / frameRate), _maxDelta(EXPECTED_MAX_DELTA / (frameRate / STANDARD_FRAMERATE)) {
    this->_componentManager = std::make_unique<ComponentManager>();
    this->_entityManager = std::make_unique<EntityManager>();
    this->_systemManager = std::make_unique<SystemManager>();
    this->_threadPool.Start();
}

EntityId Engine::createEntity() {
    return this->_entityManager->createEntity();
}

void Engine::destroyEntity(const EntityId& id)
{
    const ComponentSignature& signature = this->_entityManager->getSignature(id);

    this->_componentManager->onEntityDestroyed(id, signature);
    this->_entityManager->destroyEntity(id);
    this->_systemManager->onEntityDestroyed(id, signature);
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

    this->_systemManager->run(this->_componentManager.get());
}

void Engine::stop()
{
    this->_threadPool.Stop();
}
