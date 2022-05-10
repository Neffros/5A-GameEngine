#pragma once

#include <bitset>
#include <memory>
#include <set>
#include <unordered_map>

#include <ComponentCollection.h>
#include <EntityManager.h>

namespace GameEngine
{
	using ComponentId = std::uint16_t;

	constexpr ComponentId MAX_COMPONENTS = 64;

	using ComponentSignature = std::bitset<MAX_COMPONENTS>;

	class ComponentManager
	{
	private:
		std::unordered_map<ComponentId, std::shared_ptr<IComponentCollection>> _componentIdToCollection;
		ComponentId _currentId;
		std::array<ComponentSignature, MAX_ENTITIES> _entityToSignature;
		std::unordered_map<ComponentSignature, std::set<EntityId>> _signatureToEntities;
		std::unordered_map<std::string, ComponentId> _typeToComponentId;
	public:
		template <typename T>
		void addComponentToEntity(const EntityId& id, T component);

		template <typename T>
		T& getComponentOfEntity(const EntityId& id) const;

		std::set<EntityId> getEntitySetBySignature(const ComponentSignature& signature) const;

		void onEntityDestroyed(const EntityId& id);

		template <typename T>
		void registerComponent();

		template <typename T>
		void removeComponentOfEntity(const EntityId& id);

	private:
		template <typename T>
		std::shared_ptr<ComponentCollection<T>> getCollection(const ComponentId& id);
	};
}
