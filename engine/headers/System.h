#pragma once

#include <set>
#include <string>
#include <vector>

#include <EntityManager.h>

namespace GameEngine
{
    template <class ...Components>
    class System
    {
    protected:
        virtual void behaviour(const EntityId& id, std::tuple<Components...> components) const = 0;
    public:
        virtual void run(const std::set<EntityId>& entities/*, besoin des pack de tableaux de composants correspondant au pack de types fourni - dans le même ordre */) const;
    };
}
