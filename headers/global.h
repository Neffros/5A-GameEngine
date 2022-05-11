#pragma once

#include <array>
#include <bitset>

namespace GameEngine
{
	using EntityId = std::uint32_t;

	constexpr EntityId MAX_ENTITIES = 5000;

	using ComponentId = std::uint16_t;

	constexpr ComponentId MAX_COMPONENTS = 64;

	using ComponentSignature = std::bitset<MAX_COMPONENTS>;

	template <typename TComponent>
	using ComponentBlock = std::array<TComponent, MAX_ENTITIES>;

	struct SignatureComparer
	{
		bool operator()(const ComponentSignature& b1, const ComponentSignature& b2) const
		{
			return b1.to_ulong() < b2.to_ulong();
		}
	};
}
