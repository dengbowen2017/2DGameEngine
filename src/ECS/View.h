#pragma once

#include <tuple>

#include "ComponentPool.h"

namespace ECS
{
	template<typename... Components>
	class PoolView
	{
		using pool_iterator = std::vector<Entity>::const_iterator;

	public:
		PoolView(ComponentPool<Components>*... pools)
			:component_pools_(pools...)
		{
			size_t min_size = std::numeric_limits<size_t>::max();
			auto find_min = [&](auto* pool) {
				if (pool->Size() < min_size)
				{
					min_size = pool->Size();
					min_pool_begin_iterator = pool->begin();
					min_pool_end_iterator = pool->end();
				}
			};
			(find_min(pools), ...);
		}

		template<typename Component>
		Component& Get(Entity entity)
		{
			return std::get<ComponentPool<Component>*>(component_pools_)->Get(entity);
		}
		
		template<typename Component>
		const Component& Get(Entity entity) const
		{
			return std::get<ComponentPool<Component>*>(component_pools_)->Get(entity);
		}

	public:
		class Iterator
		{
		public:
			Iterator(std::tuple<ComponentPool<Components>*...> pools, pool_iterator it, pool_iterator end_it)
				:pools_(pools), it_(it), end_it_(end_it)
			{
				NextValid();
			}

			Entity operator*() const { return *it_; }

			Iterator& operator++()
			{
				++it_;
				NextValid();
				return *this;
			}

			bool operator!=(const Iterator& rhs) const { return it_ != rhs.it_; }

		private:
			void NextValid()
			{
				while (it_ != end_it_)
				{
					if (CheckValid())
					{
						return;
					}
					++it_;
				}
			}

			bool CheckValid() const
			{
				return (std::get<ComponentPool<Components>*>(pools_)->Contain(*it_) && ...);
			}

			std::tuple<ComponentPool<Components>*...> pools_;
			pool_iterator it_;
			pool_iterator end_it_;
		};

		Iterator begin() const { return Iterator(component_pools_, min_pool_begin_iterator, min_pool_end_iterator); }
		Iterator end() const { return Iterator(component_pools_, min_pool_end_iterator, min_pool_end_iterator); }

	private:
		std::tuple<ComponentPool<Components>*...> component_pools_;

		pool_iterator min_pool_begin_iterator;
		pool_iterator min_pool_end_iterator;
	};

}