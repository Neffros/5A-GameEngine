#pragma once

#include "../headers/ComponentManager.hpp"
#include "../headers/EntityManager.h"
#include "../headers/SystemManager.hpp"
#include "Clock.h"
#include "ThreadPool.h"

namespace GameEngine {
    class Engine
    {
    private:
        std::unique_ptr<ComponentManager> _componentManager;
        double _frameRate;
        double _frameDuration;
        double _maxDelta;
        std::unique_ptr<EntityManager> _entityManager;
        std::unique_ptr<SystemManager> _systemManager;
        Clock _clock;
        ThreadPool _threadPool;
    public:
        explicit Engine(double frameRate);

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

        void stop();
    };
}
