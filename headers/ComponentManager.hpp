#pragma once

#include <memory>
#include <set>
#include <unordered_map>

#include "../headers/ComponentCollection.hpp"
#include "../headers/EntityManager.h"
#include "../headers/global.h"

namespace GameEngine
{
	class ComponentManager
	{
	private:
		std::unordered_map<ComponentId, std::shared_ptr<IComponentCollection>> _componentIdToCollection;
		ComponentId _currentId;
		std::array<ComponentSignature, MAX_ENTITIES> _entityToSignature;
		std::unordered_map<ComponentSignature, std::set<EntityId>> _signatureToEntities;
		std::unordered_map<const char*, ComponentId> _typeToComponentId;
	public:
		template <typename TComponent>
		void addComponentToEntity(const EntityId& id, TComponent component)
		{
			const char* typeName = typeid(TComponent).name();
			const ComponentId componentId = this->_typeToComponentId[typeName];
			const ComponentSignature& oldSignature = this->_entityToSignature[id];
			ComponentSignature signature = oldSignature;

			signature.set(componentId, true);

			if (this->_signatureToEntities.count(signature) == 0)
				this->_signatureToEntities.emplace(std::make_pair(signature, std::set<EntityId>()));

			for (auto& [first, second] : this->_signatureToEntities)
			{
				if (!(oldSignature & first).test(0) && (signature & first).test(0))
					second.insert(id);
			}

			this->getCollection<TComponent>(componentId)->addData(id, component);
			this->_entityToSignature[id] = signature;
		}

		template <typename TComponent>
		TComponent& getComponentOfEntity(const EntityId& id) const
		{
			return this->getCollection<TComponent>(this->_typeToComponentId[typeid(TComponent).name])->getData(id);
		}

		std::set<EntityId> getEntitySetBySignature(const ComponentSignature& signature) const;

		void onEntityDestroyed(const EntityId& id);

		template <typename TComponent>
		void registerComponent()
		{
			const char* typeName = typeid(TComponent).name();

			this->_componentIdToCollection.emplace(std::make_pair(this->_currentId, std::make_shared<ComponentCollection<TComponent>>()));
			this->_typeToComponentId.insert({ typeName, this->_currentId });
			++this->_currentId;
		}

		template <typename TComponent>
		void removeComponentOfEntity(const EntityId& id)
		{
			const char* typeName = typeid(TComponent).name();
			const ComponentId componentId = this->_typeToComponentId[typeName];
			const ComponentSignature& oldSignature = this->_entityToSignature[id];
			ComponentSignature signature = oldSignature;

			signature.set(componentId, false);

			for (auto& [first, second] : this->_signatureToEntities)
			{
				if (!(signature & first) && (oldSignature & first))
					second.erase(id);
			}

			this->getCollection<TComponent>(componentId)->removeData(id);
			this->_entityToSignature[id] = signature;
		}

	private:
		template <typename TComponent>
		std::shared_ptr<ComponentCollection<TComponent>> getCollection(const ComponentId& id)
		{
			return std::static_pointer_cast<ComponentCollection<TComponent>>(this->_componentIdToCollection[id]);
		}
	};
}
