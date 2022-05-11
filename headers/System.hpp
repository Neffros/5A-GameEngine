#pragma once

#include <tuple>

#include "ISystem.h"

namespace GameEngine
{
	template<typename TComponent>
	ComponentSignature getComponentSignature(const ComponentManager* componentManager)
	{
		return ComponentSignature().set(componentManager->getComponentId<TComponent>(), true);
	}

	template<typename TComponent, typename TSecondComponent, typename... TComponents>
	ComponentSignature getComponentSignature(const ComponentManager* componentManager)
	{
		ComponentSignature signature;
		signature.set(componentManager->getComponentId<TComponent>(), true);
		signature |= getComponentSignature<TSecondComponent, TComponents...>(componentManager);

		return signature;
	}

	template <typename ...TComponents>
	class System : public ISystem
	{
	public:
		static ComponentSignature getSignature(const ComponentManager* componentManager)
		{
			return getComponentSignature<TComponents...>(componentManager);
		}
	private:
		template <typename TComponent>
		static TComponent& unpack(const ComponentManager* componentManager, const EntityId& id)
		{
			return componentManager->getComponentOfEntity<TComponent>(id);
		}
	public:
		virtual void run(const ComponentManager* componentManager, const std::set<EntityId>& entities) const override
		{
			for (const auto& id : entities)
			{
				this->behaviour(id, unpack<TComponents>(componentManager, id)...);
			}
		}
	protected:
		virtual void behaviour(const EntityId& id, TComponents& ...components) const = 0;
	};
}
