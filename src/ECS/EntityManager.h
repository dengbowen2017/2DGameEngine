#pragma once

#include <vector>

#include "Entity.h"

namespace ECS
{
	class EntityManager
	{
	public:
		EntityManager()
			:free_list_(EntityTrait::kNullEntity)
		{
			entities_.reserve(EntityTrait::kInitEntityNum);
		}

		bool Valide(Entity entity)
		{
			EntityDataType index = EntityTrait::GetIndex(entity);
			if (index < entities_.size())
			{
				return entity == entities_[index];
			}
			else
			{
				return false;
			}
		}

		Entity Generate()
		{
			if (free_list_ == EntityTrait::kNullEntity)
			{
				Entity new_entity = EntityTrait::Combine(0, entities_.size());
				entities_.push_back(new_entity);
				return new_entity;
			}
			else
			{
				Entity last_free_entity = entities_[free_list_];
				Entity new_entity = EntityTrait::Combine(EntityTrait::GetVersion(last_free_entity), free_list_);
				entities_[free_list_] = new_entity;
				free_list_ = EntityTrait::GetIndex(last_free_entity);
				return new_entity;
			}
		}

		void Destory(Entity entity)
		{
			ECS_ASSERT(Valide(entity));

			EntityDataType index = EntityTrait::GetIndex(entity);
			EntityDataType version = EntityTrait::GetVersion(entity);
			Entity free_list_node = EntityTrait::Combine(++version, free_list_);
			free_list_ = index;
			entities_[index] = free_list_node;
		}
	private:
		std::vector<Entity> entities_;
		EntityDataType free_list_;
	};
}