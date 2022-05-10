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
    public:
        EntityManager();

        EntityId createEntity();
        void destroyEntity(const EntityId& id);
    };
}
