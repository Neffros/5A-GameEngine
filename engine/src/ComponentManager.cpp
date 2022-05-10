#include "../headers/ComponentManager.h"

using namespace GameEngine;

template <typename T>
void ComponentManager::addComponentToEntity(const EntityId& id, T component)
{
	const ComponentId& componentId = this->_typeToComponentId[typeid(T).name];
	const ComponentSignature& oldSignature = this->_entityToSignature[id];
	ComponentSignature signature = oldSignature;

	signature.set(componentId, true);

	if (this->_signatureToEntities.count(signature) == 0)
		this->_signatureToEntities.insert({ signature, std::array<ComponentSignature, MAX_ENTITIES>() });

	for (auto& [first, second] : this->_signatureToEntities)
	{
		if (!(oldSignature & first) && (signature & first))
			second.insert(id);
	}

	this->getCollection<T>(componentId)->addData(id, component);
	this->_entityToSignature[id] = signature;
}

template <typename T>
T& ComponentManager::getComponentOfEntity(const EntityId& id) const
{
	return this->getCollection<T>(this->_typeToComponentId[typeid(T).name])->getData(id);
}

std::set<EntityId> ComponentManager::getEntitySetBySignature(const ComponentSignature& signature) const
{
	return this->_signatureToEntities.at(signature);
}

void ComponentManager::onEntityDestroyed(const EntityId& id)
{
	const ComponentSignature& signature = this->_entityToSignature[id];

	for (size_t index = 0; index < signature.size(); ++index)
		this->_componentIdToCollection[signature[index]]->removeData(id);

	this->_signatureToEntities[signature].erase(id);
	this->_entityToSignature[id].reset();
}

template <typename T>
void ComponentManager::registerComponent()
{
	const char* typeName = typeid(T).name();

	this->_componentIdToCollection.insert({ this->_currentId, std::make_shared<ComponentCollection<T>>() });
	this->_typeToComponentId.insert({ typeName, this->_currentId });
	++this->_currentId;
}

template <typename T>
void ComponentManager::removeComponentOfEntity(const EntityId& id)
{
	const ComponentId& componentId = this->_typeToComponentId[typeid(T).name];
	const ComponentSignature& oldSignature = this->_entityToSignature[id];
	ComponentSignature signature = oldSignature;

	signature.set(componentId, false);

	for (auto& [first, second] : this->_signatureToEntities)
	{
		if (!(signature & first) && (oldSignature & first))
			second.erase(id);
	}

	this->getCollection<T>(componentId)->removeData(id);
	this->_entityToSignature[id] = signature;
}

template <typename T>
std::shared_ptr<ComponentCollection<T>> ComponentManager::getCollection(const ComponentId& id)
{
	return std::static_pointer_cast<ComponentCollection<T>>(this->_componentIdToCollection[id]);
}
