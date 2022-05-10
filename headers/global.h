#pragma once

#include <bitset>

namespace GameEngine
{
	using EntityId = std::uint32_t;

	constexpr EntityId MAX_ENTITIES = 5000;

	using ComponentId = std::uint16_t;

	constexpr ComponentId MAX_COMPONENTS = 64;

	using ComponentSignature = std::bitset<MAX_COMPONENTS>;
}
