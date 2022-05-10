#pragma once

#include "EntityManager.h"

namespace GameEngine
{
	class IComponentCollection
	{
	public:
		virtual void removeData(EntityId id) = 0;
	};
}
