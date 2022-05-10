#pragma once

#include <tuple>

#include "../headers/ISystem.h"

namespace GameEngine
{
    template <class ...Components>
    class System : ISystem
    {
    protected:
        virtual void behaviour(const EntityId& id, std::tuple<Components...> components) const = 0;
    public:
        void run(const std::set<EntityId>& entities) const override
        {
            for(auto entity : entities){

            }
        }
    };
}
