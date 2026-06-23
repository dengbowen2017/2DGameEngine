#pragma once

#include <cstdint>
#include <cassert>

#ifdef GE_DEBUG
#define ECS_ASSERT(expr) assert(expr)
#else
#define ECS_ASSERT(expr) ((void)0)
#endif // DEBUG

namespace ECS
{
	using EntityType = uint32_t;

	enum class Entity : EntityType;

	struct EntityTrait
	{
		static constexpr EntityType kBitShift = 20;
		static constexpr EntityType kIndexMask = (1U << kBitShift) - 1;
		static constexpr EntityType kNullEntity = kIndexMask;
		static constexpr size_t kInitEntityNum = 10000;

		static EntityType GetVersion(Entity entity)
		{
			return static_cast<EntityType>(entity) >> kBitShift;
		}

		static EntityType GetIndex(Entity entity)
		{
			return static_cast<EntityType>(entity) & kIndexMask;
		}

		static Entity Combine(EntityType version, EntityType index)
		{
			return static_cast<Entity>((version << kBitShift) | index);
		}
	};
}