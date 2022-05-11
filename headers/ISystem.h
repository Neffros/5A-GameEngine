#pragma once

#include <set>

#include "ComponentManager.hpp"
#include "global.h"

namespace GameEngine
{
    class Engine;

    struct ISystem
    {
        virtual void run(Engine* engine, const std::set<EntityId>& entities) const = 0;
    };
}
