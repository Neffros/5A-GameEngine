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
		void run(Engine* engine, const std::set<EntityId>& entities) const override
		{
            std::vector<int> runningThreads;
			for (const auto& id : entities) {
                runningThreads.push_back(engine->threadPool()->QueueJob([this, id, engine] {
                    this->behaviour(id, unpack<TComponents>(engine, id)...);
                }));
            }
            // wait for all
            for(int i = runningThreads.size()-1; i >= 0; --i){
                engine->threadPool()->WaitForJob(runningThreads[i]);
            }
		}
	protected:
		virtual void behaviour(const EntityId& id, TComponents& ...components) const = 0;
	};
}
