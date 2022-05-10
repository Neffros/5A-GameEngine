#pragma once

#include <map>
#include "ComponentManager.h"
#include "System.h"
#include "RTTI.h"

namespace GameEngine {
    template<class T>
    class SystemManager {
    private:
        std::map<ComponentSignature, std::unique_ptr<System<T>>> _signatureToSystems;
        std::vector<std::unique_ptr<System<T>>> _systems;
    public:
        void registerSystem(ComponentSignature signature);
        void registerSystem(RTTI<T> rtti, ComponentSignature signature);
    };
}