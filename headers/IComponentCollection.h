#pragma once

#include "../headers/global.h"

namespace GameEngine
{
	class IComponentCollection
	{
	public:
		virtual void removeData(EntityId id) = 0;
	};
}
