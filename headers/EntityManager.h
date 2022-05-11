#pragma once

#include <array>
#include <queue>

#include "../headers/global.h"
#include <map>

namespace GameEngine
{
    class EntityManager
    {
    private:
        std::queue<EntityId> _availableEntities;
        std::array<ComponentSignature, MAX_ENTITIES> _entityToSignature;
        std::array<std::string, MAX_ENTITIES> _entityToTag;
        std::map<std::string, std::vector<EntityId>> _tagToEntities;
    public:
        EntityManager();
        std::vector<EntityId> getEntitiesByTag(std::string& tag);
        EntityId createEntity(const std::string& tag = "");
        void destroyEntity(const EntityId& id);
        ComponentSignature getSignature(const EntityId& id) const;
        void setSignature(const EntityId& id, ComponentSignature signature);
    };
}
