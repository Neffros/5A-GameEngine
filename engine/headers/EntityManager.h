#pragma once

#include <queue>

namespace GameEngine
{
    using EntityId = std::uint32_t;
    
    constexpr EntityId MAX_ENTITIES = 5000;

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
