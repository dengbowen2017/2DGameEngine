#pragma once

#include <memory>
#include <vector>

#include "ComponentPool.h"

namespace ECS
{
	class ComponentManager
	{
	public:
		ComponentManager() = default;

		void Clear(Entity entity)
		{
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
			return GetPool<Component>()->Get(entity);
		}

		template<typename Component>
		const Component& Get(Entity entity) const
		{
			return GetPool<Component>()->Get(entity);
		}

		template<typename Component>
		bool Contain(Entity entity) const
		{
			return GetPool<Component>()->Contain(entity);
		}

		template<typename Component, typename... Args>
		Component& Emplace(Entity entity, Args&&... args)
		{
			return AssurePool<Component>().Emplace(entity, std::forward<Args>(args)...);
		}

		template<typename Component>
		void Erase(Entity entity)
		{
			return GetPool<Component>()->Remove(entity);
		}

		template<typename Component>
		ComponentPool<Component>* GetPool()
		{
			ECS_ASSERT(ComponentPool<Component>::ID() < component_pools_.size());
			return static_cast<ComponentPool<Component>*>(component_pools_[ComponentPool<Component>::ID()].get());
		}

	private:
		template<typename Component>
		ComponentPool<Component>& AssurePool()
		{
			size_t pool_id = ComponentPool<Component>::ID();
			if (pool_id >= component_pools_.size())
			{
				component_pools_.resize(pool_id);
				component_pools_.emplace_back(std::make_unique<ComponentPool<Component>>());
			}

			return *static_cast<ComponentPool<Component>*>(component_pools_[pool_id].get());
		}

		std::vector<std::unique_ptr<BaseComponentPool>> component_pools_;
	};
}