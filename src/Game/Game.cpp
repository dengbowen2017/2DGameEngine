#include "Game.h"

#include "GameObject.h"

namespace GE
{
	GameObject Game::CreateGameObject()
	{
		return GameObject(registry_.Create(), this);
	}
}