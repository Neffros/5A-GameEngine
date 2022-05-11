#pragma once

#include "Clock.h"
#include "ComponentManager.hpp"
#include "EntityManager.h"
#include "MultiDelegate.hpp"
#include "SystemManager.hpp"
#include "ThreadPool.h"

namespace GameEngine {
	struct EngineEvents
	{
		MultiDelegate<void(const EntityId&, const ComponentSignature&, const ComponentSignature&)> onComponentAddedToEntity;
		MultiDelegate<void(const EntityId&, const ComponentSignature&, const ComponentSignature&)> onComponentRemovedFromEntity;
		MultiDelegate<void(const EntityId&, const ComponentSignature&)> onEntityDestroyed;
	};

    class Engine : EngineEvents
    {
    private:
		Clock _clock;
        std::unique_ptr<ComponentManager> _componentManager;
        double _frameRate;
		double _frameDuration;
        std::unique_ptr<EntityManager> _entityManager;
		double _maxDelta;
        std::unique_ptr<SystemManager> _systemManager;
		std::unique_ptr<ThreadPool> _threadPool;
    public:
        explicit Engine(double frameRate);

		template <typename TComponent>
		void addComponent(const EntityId& id, TComponent component)
		{
			const ComponentId& componentId = this->_componentManager->addComponentToEntity<TComponent>(id, component);
			const ComponentSignature& oldSignature = this->_entityManager->getSignature(id);
			ComponentSignature newSignature = oldSignature;

			newSignature.set(componentId, true);
			this->_entityManager->setSignature(id, newSignature);
			this->onComponentAddedToEntity.invoke(id, oldSignature, newSignature);
		}

		EntityId createEntity();

		void destroyEntity(const EntityId& id);

		template<typename TComponent>
		TComponent& getComponent(const EntityId& id)
		{
			return this->_componentManager->getComponentOfEntity<TComponent>(id);
		}

		template <typename TComponent>
		ComponentId getComponentId() const
		{
			return this->_componentManager->getComponentId<TComponent>();
		}

        ThreadPool* getThreadPool();

		template<typename TComponent>
		void registerComponent()
		{
			this->_componentManager->registerComponent<TComponent>();
		}

		template<typename TSystem>
		void registerSystem()
		{
			this->_systemManager->registerSystem<TSystem>(TSystem::getSignature(this));
		}

		template<typename TComponent>
		void removeComponent(const EntityId& id)
		{
			const ComponentId& componentId = this->_componentManager->removeComponentOfEntity<TComponent>(id);
			const ComponentSignature& oldSignature = this->_entityManager->getSignature(id);
			ComponentSignature newSignature = oldSignature;

			newSignature.set(componentId, false);
			this->_entityManager->setSignature(id, newSignature);
			this->onComponentRemovedFromEntity.invoke(id, oldSignature, newSignature);
		}

        void tick();

        void stop();
    };
}
