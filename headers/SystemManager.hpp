#pragma once

#include <set>
#include <unordered_map>

#include "global.h"
#include "ISystem.h"
#include "System.hpp"

namespace GameEngine
{
    class SystemManager
    {
    private:
        std::unordered_map<ComponentSignature, std::set<EntityId>> _signatureToEntities;
        std::unordered_map<ComponentSignature, std::unique_ptr<ISystem>> _signatureToSystems;
        std::vector<std::unique_ptr<ISystem>> _systems;
    public:
        template<typename TSystem>
        void registerSystem(ComponentSignature signature)
        {
            const std::unique_ptr<TSystem>& system = std::make_unique<TSystem>();

            this->_systems.push_back(system);
            this->_signatureToSystems.emplace({ signature, system });
        }
    };
}
