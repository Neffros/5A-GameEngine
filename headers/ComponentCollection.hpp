#pragma once

#include <array>
#include <unordered_map>

#include "EntityManager.h"
#include "IComponentCollection.h"

namespace GameEngine
{
	// TODO: Potentiellement remplacer par une classe de collection utilisant un pool d'allocation
	template <typename TComponent>
	class ComponentCollection : public IComponentCollection
	{
	private:
		ComponentBlock<TComponent> _componentLookup;
		size_t _currentIndex;
		std::unordered_map<EntityId, size_t> _entityToIndexLookup;
		std::unordered_map<size_t, EntityId> _indexToEntityLookup;
	public:
		void addData(EntityId id, TComponent data)
		{
			this->_entityToIndexLookup[id] = this->_currentIndex;
			this->_indexToEntityLookup[this->_currentIndex] = id;
			this->_componentLookup[this->_currentIndex] = data;
			++this->_currentIndex;
		}

		TComponent& getData(EntityId id)
		{
			return this->_componentLookup[this->_entityToIndexLookup[id]];
		}

		void removeData(EntityId id) override
		{
			--this->_currentIndex;

			size_t removedEntityIndex = this->_entityToIndexLookup[id];

			this->_componentLookup[removedEntityIndex] = this->_componentLookup[this->_currentIndex];

			EntityId lastIndexEntityId = this->_indexToEntityLookup[this->_currentIndex];

			this->_entityToIndexLookup[lastIndexEntityId] = removedEntityIndex;
			this->_indexToEntityLookup[removedEntityIndex] = lastIndexEntityId;

			this->_entityToIndexLookup.erase(id);
			this->_indexToEntityLookup.erase(this->_currentIndex);
		}
	};
}
