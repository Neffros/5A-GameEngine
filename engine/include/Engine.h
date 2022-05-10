#pragma once

#include "SystemManager.h"
#include "EntityManager.h"
#include "ComponentManager.h"

namespace GameEngine {
    class Engine{
    private:
        double frameRate;
        //time of type time component

        //SystemManager cant implement because requires template currently
        SystemManager systemManager;
        EntityManager entityManager;
        ComponentManager componentManager;
    public:
        EntityId createEntity();
        void destroyEntity(EntityId id);

        void addComponent(EntityId entityId, ComponentId componentId);
        template<typename TComponent>
        TComponent getComponent(EntityId entityId);

        template<typename TComponent>
        void registerComponent();

        template<typename TComponent>
        void removeComponent(EntityId entityId);

        template<typename TSystem>
        void RegisterSystem();

        void tick();
    };
}