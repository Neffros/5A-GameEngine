#include "../headers/ComponentManager.hpp"

using namespace GameEngine;

void ComponentManager::onEntityDestroyed(const EntityId& id, const ComponentSignature& signature)
{
	for (size_t index = 0; index < signature.size(); ++index)
		this->_componentIdToCollection[signature[index]]->removeData(id);
}
