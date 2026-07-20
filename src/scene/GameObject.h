#pragma once

#include "ECS/Entity.h"
#include "Game.h"

namespace GE
{
	class GameObject
	{
	public:
		GameObject() = default;

		GameObject(ECS::Entity entity, Game* game)
			:entity_(entity), game_(game)
		{}

		template<typename T, typename... Args>
		T& AddComponent(Args&&... args)
		{
			return game_->registry_.Emplace<T>(entity_, std::forward<Args>(args)...);
		}

		template<typename T>
		T& GetComponent()
		{
			return game_->registry_.Get<T>(entity_);
		}

	private:
		ECS::Entity entity_;
		Game* game_;
	};
}
