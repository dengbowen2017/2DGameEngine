#pragma once

#include "ECS/Registry.h"

namespace GE
{
	class GameObject;

	class Game
	{
		friend class GameObject;
	public:
		Game() = default;

		GameObject CreateGameObject();

	private:
		ECS::Registry registry_;
	};
}