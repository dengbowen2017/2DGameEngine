#include "InputSystem.h"

#include <SDL3/SDL.h>
#include <spdlog/spdlog.h>

namespace VS
{
	InputSystem::InputSystem()
		:is_quit_(false)
	{
		key_state_ = SDL_GetKeyboardState(nullptr);
		RegisterKeys();
	}

	void InputSystem::Update()
	{
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_EVENT_QUIT) {
				is_quit_ = true;
			}
		}
	}

	bool InputSystem::GetKey(const std::string& key_name)
	{
		return key_state_[key_map_[key_name]];
	}

	void InputSystem::RegisterKeys()
	{
		key_map_["A"] = SDL_Scancode::SDL_SCANCODE_A;
		key_map_["D"] = SDL_Scancode::SDL_SCANCODE_D;
	}
}

