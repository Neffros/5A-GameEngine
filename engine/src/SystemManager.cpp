#include "../headers/SystemManager.h"

using namespace GameEngine;

template<typename T>
void SystemManager::registerSystem(ComponentSignature signature, System<T>) {
    auto system = std::make_unique<System<T>>();
    _systems.push_back(system);
    _signatureToSystems.emplace({signature, system});
}

template<class T>
void SystemManager::registerSystem(RTTI<T> rtti, ComponentSignature signature) {

}
