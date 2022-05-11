#pragma once

#include <tuple>

#include "Engine.hpp"
#include "ISystem.h"

namespace GameEngine
{
	template<typename TComponent>
	ComponentSignature getComponentSignature(const Engine* engine)
	{
		return ComponentSignature().set(engine->getComponentId<TComponent>(), true);
	}

	template<typename TComponent, typename TSecondComponent, typename... TComponents>
	ComponentSignature getComponentSignature(const Engine* engine)
	{
		ComponentSignature signature;
		signature.set(engine->getComponentId<TComponent>(), true);
		signature |= getComponentSignature<TSecondComponent, TComponents...>(engine);

		return signature;
	}

	template <typename ...TComponents>
	class System : public ISystem
	{
	public:
		static ComponentSignature getSignature(const Engine* engine)
		{
			return getComponentSignature<TComponents...>(engine);
		}
	private:
		template <typename TComponent>
		static TComponent& unpack(Engine* engine, const EntityId& id)
		{
			return engine->getComponent<TComponent>(id);
		}
	public:
		virtual void run(Engine* engine, const std::set<EntityId>& entities) const override
		{
			for (const auto& id : entities)
				this->behaviour(id, unpack<TComponents>(engine, id)...);
		}
	protected:
		virtual void behaviour(const EntityId& id, TComponents& ...components) const = 0;
	};
}
