#pragma once

#include <memory>

#include "EntityManager.h"
#include "ComponentManager.h"
#include "View.h"

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

		bool Valid(Entity entity) const 
		{
			return entity_mgr_.Valid(entity);
		}

		void Destory(Entity entity)
		{
			ECS_ASSERT(Valid(entity));

			component_mgr_.Clear(entity);
			entity_mgr_.Destory(entity);
		}

		template<typename Component>
		Component& Get(Entity entity)
		{
			ECS_ASSERT(Valid(entity));
			return component_mgr_.Get<Component>(entity);
		}

		template<typename Component>
		const Component& Get(Entity entity) const
		{
			ECS_ASSERT(Valid(entity));
			return component_mgr_.Get<Component>(entity);
		}

		template<typename Component>
		bool Contain(Entity entity) const
		{
			ECS_ASSERT(Valid(entity));
			return component_mgr_.Contain(entity);
		}

		template<typename Component, typename... Args>
		Component& Emplace(Entity entity, Args&&... args)
		{
			ECS_ASSERT(Valid(entity));
			return component_mgr_.Emplace<Component>(entity, std::forward<Args>(args)...);
		}

		template<typename Component>
		void Erase(Entity entity)
		{
			ECS_ASSERT(Valid(entity));
			return component_mgr_.Erase<Component>(entity);
		}

		template<typename... Components>
		PoolView<Components...> View()
		{
			return PoolView<Components...>(component_mgr_.GetPool<Components>()...);
		}

	private:
		EntityManager entity_mgr_;
		ComponentManager component_mgr_;
	};
}