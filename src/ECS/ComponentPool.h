#pragma once

#include <vector>

#include "Entity.h"

namespace ECS
{
	class BaseComponentPool
	{
	public:
		virtual ~BaseComponentPool() = default;

	protected:
		static size_t Next()
		{
			static int count = 0;
			return count++;
		}
	};

	template <typename Component>
	class ComponentPool : BaseComponentPool
	{
	public:
		ComponentPool()
		{
			sparse_.reserve(EntityTrait::kInitEntityNum);
			dense_.reserve(EntityTrait::kInitEntityNum);
			components_.reserve(EntityTrait::kInitEntityNum);
		}

		static size_t ID()
		{
			static int id = Next();
			return id;
		}

		bool Contain(Entity entity)
		{
			EntityDataType index = EntityTrait::GetIndex(entity);
			if (index < sparse_.size())
			{
				if (sparse_[index] != EntityTrait::kNullEntity)
				{
					return dense_[sparse_[index]] == entity;
				}
			}
			return false;
		}

		template<typename... Args>
		Component& Emplace(Entity entity, Args&&... args)
		{
			ECS_ASSERT(!Contain(entity));

			EntityDataType index = EntityTrait::GetIndex(entity);
			if (index >= sparse_.size())
			{
				sparse_.resize(index + 1, EntityTrait::kNullEntity);
			}
			
			sparse_[index] = dense_.size();
			dense_.push_back(entity);
			components_.emplace_back(std::forward<Args>(args)...);
			return components_.back();
		}

		void Remove(Entity entity)
		{
			ECS_ASSERT(Contain(entity));

			EntityDataType delete_index = EntityTrait::GetIndex(entity);
			EntityDataType last_index = EntityTrait::GetIndex(dense_.back());

			dense_[sparse_[delete_index]] = dense_.back();
			std::swap(components_[sparse_[delete_index]], components_.back());
			sparse_[last_index] = sparse_[delete_index];

			sparse_[delete_index] = EntityTrait::kNullEntity;
			dense_.pop_back();
			components_.pop_back();
		}

		Component& Get(Entity entity)
		{
			ECS_ASSERT(Contain(entity));

			EntityDataType index = EntityTrait::GetIndex(entity);
			return components_[sparse_[index]];
		}

		const Component& Get(Entity entity) const
		{
			ECS_ASSERT(Contain(entity));

			EntityDataType index = EntityTrait::GetIndex(entity);
			return components_[sparse_[index]];
		}

	public:
		using iterator = std::vector<Entity>::iterator;
		iterator begin() { return dense_.begin(); }
		iterator end() { return dense_.end(); }

	private:
		std::vector<EntityDataType> sparse_;
		std::vector<Entity> dense_;

		std::vector<Component> components_;
	};
}