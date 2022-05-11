#include "../headers/SystemManager.hpp"

using namespace GameEngine;

void SystemManager::onComponentAddedToEntity(const EntityId& id, const ComponentSignature& oldSignature, const ComponentSignature& newSignature)
{
	for (auto& [signature, group] : this->_signatureToGroup)
	{
		if ((oldSignature & signature) != signature && (newSignature & signature) == signature)
			group.entities.insert(id);
	}
}

void SystemManager::onComponentRemovedToEntity(const EntityId& id, const ComponentSignature& oldSignature, const ComponentSignature& newSignature)
{
	for (auto& [signature, group] : this->_signatureToGroup)
	{
		if ((oldSignature & signature) == signature && (newSignature & signature) != signature)
			group.entities.erase(id);
	}

}

void SystemManager::onEntityDestroyed(const EntityId& id, const ComponentSignature& signature)
{
	this->_signatureToGroup[signature].entities.erase(id);
}

void SystemManager::run(Engine* engine) const
{
	for (const auto& [_, group] : this->_signatureToGroup)
	{
		for (const auto& system : group.systems)
			system->run(engine, group.entities);
	}
}
