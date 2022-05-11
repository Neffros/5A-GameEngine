#pragma once

#include <set>

#include "ComponentManager.hpp"
#include "global.h"

namespace GameEngine
{
    struct ISystem
    {
        virtual void run(const ComponentManager* componentManager, const std::set<EntityId>& entities) const = 0;
    };
}
