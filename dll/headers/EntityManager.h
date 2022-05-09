#pragma once

#include <queue>
#include <array>
#include "Utils.h"
using EntityID = uint32_t;
#define MAX_ENTITIES 10000

namespace GameEngine {
    class DllEngine EntityManager {
    private:
        std::queue<EntityID> availableEntities;
    public:
        EntityManager();
        EntityID createEntity();

        void destroyEntity(EntityID id);

    };
}
