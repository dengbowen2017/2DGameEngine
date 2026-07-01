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
	using EntityDataType = uint32_t;

	enum class Entity : EntityDataType;

	struct EntityTrait
	{
		static constexpr EntityDataType kBitShift = 20;
		static constexpr EntityDataType kIndexMask = (1U << kBitShift) - 1;
		static constexpr EntityDataType kNullEntity = kIndexMask;
		static constexpr size_t kInitEntityNum = 10000;

		static EntityDataType GetVersion(Entity entity)
		{
			return static_cast<EntityDataType>(entity) >> kBitShift;
		}

		static EntityDataType GetIndex(Entity entity)
		{
			return static_cast<EntityDataType>(entity) & kIndexMask;
		}

		static Entity Combine(EntityDataType version, EntityDataType index)
		{
			return static_cast<Entity>((version << kBitShift) | index);
		}
	};
}