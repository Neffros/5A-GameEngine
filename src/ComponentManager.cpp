#include "../headers/ComponentManager.hpp"

using namespace GameEngine;

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
