#pragma once

#include <map>
#include <memory>
#include <set>

#include "../headers/ComponentCollection.hpp"
#include "../headers/EntityManager.h"
#include "../headers/global.h"

namespace GameEngine
{
	class ComponentManager
	{
	private:
		std::map<ComponentId, std::shared_ptr<IComponentCollection>> _componentIdToCollection;
		ComponentId _currentId;
		std::unordered_map<const char*, ComponentId> _typeToComponentId;
	public:
		template <typename TComponent>
		ComponentId addComponentToEntity(const EntityId& id, TComponent component)
		{
			const ComponentId& componentId = this->getComponentId<TComponent>();
			this->getCollection<TComponent>(componentId)->addData(id, component);

			return componentId;
		}

		template <typename TComponent>
		ComponentId getComponentId() const
		{
			return this->_typeToComponentId.at(typeid(TComponent).name());
		}

		template <typename TComponent>
		TComponent& getComponentOfEntity(const EntityId& id) const
		{
			return this->getCollection<TComponent>(this->getComponentId<TComponent>())->getData(id);
		}

		void onEntityDestroyed(const EntityId& id, const ComponentSignature& signature);

		template <typename TComponent>
		void registerComponent()
		{
			const char* typeName = typeid(TComponent).name();

			this->_componentIdToCollection.emplace(std::make_pair(this->_currentId, std::make_shared<ComponentCollection<TComponent>>()));
			this->_typeToComponentId.insert({ typeName, this->_currentId });
			++this->_currentId;
		}

		template <typename TComponent>
		ComponentId removeComponentOfEntity(const EntityId& id)
		{
			const ComponentId& componentId = this->getComponentId<TComponent>();
			this->getCollection<TComponent>(componentId)->removeData(id);

			return componentId;
		}


	private:
		template <typename TComponent>
		std::shared_ptr<ComponentCollection<TComponent>> getCollection(const ComponentId& id) const
		{
			return std::static_pointer_cast<ComponentCollection<TComponent>>(this->_componentIdToCollection.at(id));
		}
	};
}
