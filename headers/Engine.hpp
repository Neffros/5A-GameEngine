#pragma once

#include "../headers/ComponentManager.hpp"
#include "../headers/EntityManager.h"
#include "../headers/SystemManager.hpp"

namespace GameEngine
{
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
			const ComponentId& componentId = this->_componentManager->addComponentToEntity<TComponent>(id, component);
			const ComponentSignature& oldSignature = this->_entityManager->getSignature(id);
			ComponentSignature newSignature = oldSignature;

			newSignature.set(componentId, true);
			this->_entityManager->setSignature(id, newSignature);
			this->_systemManager->onComponentAddedToEntity(id, oldSignature, newSignature);
		}

		EntityId createEntity();

		void destroyEntity(const EntityId& id);

		template<typename TComponent>
		TComponent& getComponent(const EntityId& id)
		{
			return this->_componentManager->getComponentOfEntity<TComponent>(id);
		}

		template <typename TComponent>
		ComponentId getComponentId()
		{
			return this->_componentManager->getComponentId<TComponent>();
		}

		template<typename TComponent>
		void registerComponent()
		{
			this->_componentManager->registerComponent<TComponent>();
		}

		template<typename TSystem>
		void registerSystem()
		{
			this->_systemManager->registerSystem<TSystem>(TSystem::getSignature(this->_componentManager.get()));
		}

		template<typename TComponent>
		void removeComponent(const EntityId& id)
		{
			const ComponentId& componentId = this->_componentManager->removeComponentOfEntity<TComponent>(id);
			const ComponentSignature& oldSignature = this->_entityManager->getSignature(id);
			ComponentSignature newSignature = oldSignature;

			newSignature.set(componentId, false);
			this->_entityManager->setSignature(id, newSignature);
			this->_systemManager->onComponentRemovedToEntity(id, oldSignature, newSignature);
		}

		void tick();
	};
}
