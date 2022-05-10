#include "../headers/SystemManager.h"

using namespace GameEngine;

template<class T>
void SystemManager<T>::registerSystem(ComponentSignature signature) {
    auto system = std::make_unique<System<T>>();
    _systems.push_back(system);
    _signatureToSystems.emplace({signature, system});
}

template<class T>
void SystemManager<T>::registerSystem(RTTI<T> rtti, ComponentSignature signature) {

}
