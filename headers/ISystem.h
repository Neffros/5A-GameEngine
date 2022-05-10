#pragma once

#include <set>

#include "../headers/EntityManager.h"

namespace GameEngine
{
    class ISystem
    {
        virtual void run(const std::set<EntityId>& entities/*, besoin des pack de tableaux de composants correspondant au pack de types fourni - dans le même ordre */) const = 0;
    };
}
