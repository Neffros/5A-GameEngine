#pragma once

#include <map>
#include "ComponentManager.h"
#include "System.h"
#include "RTTI.h"

namespace GameEngine {
    class SystemManager {
    private:
        std::map<ComponentSignature, std::unique_ptr<ISystem>> _signatureToSystems;
        std::vector<std::unique_ptr<ISystem>> _systems;
    public:
        template<typename T>
        void registerSystem(ComponentSignature signature, System<T>);
        template<typename T>
        void registerSystem(RTTI<T> rtti, ComponentSignature signature);
    };
}