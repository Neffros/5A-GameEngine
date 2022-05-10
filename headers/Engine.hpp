#pragma once

#include "../headers/ComponentManager.hpp"
#include "../headers/EntityManager.h"
#include "../headers/SystemManager.hpp"

namespace GameEngine {
    class Engine
    {
    private:
        std::unique_ptr<ComponentManager> _componentManager;
        double _frameRate;
        std::unique_ptr<EntityManager> _entityManager;
        std::unique_ptr<SystemManager> _systemManager;
    public:
        Engine();

        template <typename TComponent>
        void addComponent(const EntityId& id, TComponent component)
        {
            this->_componentManager->addComponentToEntity<TComponent>(id, component);
        }

        EntityId createEntity();

        void destroyEntity(const EntityId& id);

        template<typename TComponent>
        TComponent getComponent(const EntityId& id)
        {
            return this->_componentManager->getComponentOfEntity<TComponent>(id);
        }

        template<typename TComponent>
        void registerComponent()
        {
            this->_componentManager->registerComponent<TComponent>();
        }

        template<typename TSystem>
        void registerSystem()
        {
            this->_systemManager->registerSystem<TSystem>();
        }

        template<typename TComponent>
        void removeComponent(const EntityId& id)
        {
            this->_componentManager->removeComponentOfEntity<TComponent>(id);
        }

        void tick();
    };
}
