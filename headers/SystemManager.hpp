#pragma once

#include <map>
#include <memory>
#include <set>

#include "global.h"
#include "ISystem.h"

namespace GameEngine
{
    class Engine;

    struct SignatureGroup
    {
        std::set<EntityId> entities;
        std::vector<std::shared_ptr<ISystem>> systems;
    };

    class SystemManager
    {
    private:
        std::map<ComponentSignature, SignatureGroup, SignatureComparer> _signatureToGroup;
    public:
        void onComponentAddedToEntity(const EntityId& id, const ComponentSignature& oldSignature, const ComponentSignature& newSignature);

        void onComponentRemovedFromEntity(const EntityId& id, const ComponentSignature& oldSignature, const ComponentSignature& newSignature);

        void onEntityDestroyed(const EntityId& id, const ComponentSignature& signature);

        template<typename TSystem>
        void registerSystem(ComponentSignature signature)
        {
            std::shared_ptr<ISystem> system = std::make_shared<TSystem>();

            if (!this->_signatureToGroup.contains(signature))
                this->_signatureToGroup.emplace(std::make_pair(signature, SignatureGroup{}));

            this->push(signature, system);
        }

        void run(Engine* engine) const;
    private:
        void push(const ComponentSignature& signature, std::shared_ptr<ISystem> system)
        {
            this->_signatureToGroup[signature].systems.push_back(system);
        }
    };
}
