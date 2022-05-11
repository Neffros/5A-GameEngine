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
			this->forEach(engine, entities, [this](const EntityId& id, TComponents& ...components) {
				this->behaviour(id, components...);
				});
		}
	protected:
		virtual void behaviour(const EntityId& id, TComponents& ...components) const = 0;

		// TODO : fournir la lambda à utiliser qui prend en paramètre entity et components
		void forEach(Engine* engine, const std::set<EntityId>& entities, const std::function<void(const EntityId&, TComponents&...)>& job) const
		{
			std::vector<int> jobIds;

			for (const auto& id : entities)
				jobIds.push_back(engine->getThreadPool()->queueJob([this, id, job, engine] { job(id, unpack<TComponents>(engine, id)...); }));

			for (const auto& jobId : jobIds)
				engine->getThreadPool()->waitForJob(jobId);
		}
	};
}
