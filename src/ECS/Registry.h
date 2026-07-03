#pragma once

#include <memory>

#include "EntityManager.h"
#include "ComponentPool.h"

namespace ECS
{
	class Registry
	{
	public:
		Registry() = default;

		Entity Create()
		{
			return entity_mgr_.Generate();
		}

		bool Valid(Entity entity)
		{
			return entity_mgr_.Valid(entity);
		}

		void Destory(Entity entity)
		{
			ECS_ASSERT(Valid(entity));

			for (auto& pool : component_pools_)
			{
				if (pool->Contain(entity))
				{
					pool->Remove(entity);
				}
			}
		}

		template<typename Component>
		Component& Get(Entity entity)
		{
			ECS_ASSERT(Valid(entity));
			return GetPool<Component>()->Get(entity);
		}

		template<typename Component>
		const Component& Get(Entity entity) const
		{
			ECS_ASSERT(Valid(entity));
			return GetPool<Component>()->Get(entity);
		}

		template<typename Component>
		bool Contain(Entity entity)
		{
			ECS_ASSERT(Valid(entity));
			return GetPool<Component>()->Contain(entity);
		}

		template<typename Component, typename... Args>
		Component& Emplace(Entity entity, Args&&... args)
		{
			ECS_ASSERT(Valid(entity));
			return AssurePool<Component>().Emplace(entity, std::forward<Args>(args)...);
		}

		template<typename Component>
		void Erase(Entity entity)
		{
			ECS_ASSERT(Valid(entity));
			return GetPool<Component>()->Remove(entity);
		}

		//template<typename... Component>
		//void View()
		//{

		//}

	private:
		template<typename Component>
		ComponentPool<Component>& AssurePool()
		{
			size_t pool_id = ComponentPool<Component>::ID();
			if (pool_id >= component_pools_.size())
			{
				component_pools_.resize(pool_id + 1);
				component_pools_[pool_id] = std::make_unique<ComponentPool<Component>>();
			}
			return *static_cast<ComponentPool<Component>*>(component_pools_[pool_id].get());
		}

		template<typename Component>
		ComponentPool<Component>* GetPool()
		{
			ECS_ASSERT(ComponentPool<Component>::ID() < component_pools_.size());
			return static_cast<ComponentPool<Component>*>(component_pools_[ComponentPool<Component>::ID()].get());
		}

		EntityManager entity_mgr_;
		std::vector<std::unique_ptr<BaseComponentPool>> component_pools_;
	};
}