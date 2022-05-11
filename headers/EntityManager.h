#pragma once

#include <array>
#include <queue>

#include "../headers/global.h"

namespace GameEngine
{
    class EntityManager
    {
    private:
        std::queue<EntityId> _availableEntities;
        std::array<ComponentSignature, MAX_ENTITIES> _entityToSignature;
    public:
        EntityManager();

        EntityId createEntity();
        void destroyEntity(const EntityId& id);
        ComponentSignature getSignature(const EntityId& id) const;
        void setSignature(const EntityId& id, ComponentSignature signature);
    };
}
