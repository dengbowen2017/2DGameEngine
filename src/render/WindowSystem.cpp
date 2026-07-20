#include "WindowSystem.h"

#include <iostream>

#include <SDL3/SDL.h>

namespace VS
{
	WindowSystem::WindowSystem()
		:window_(nullptr)
	{
		if (!SDL_Init(SDL_INIT_VIDEO)) {
			std::cerr << "Failed to init SDL: " << SDL_GetError() << std::endl;
			return;
		}

		window_ = SDL_CreateWindow("2D Game", 1280, 960, 0);
		if (!window_)
		{
			std::cerr << "Failed to create SDL_Window: " << SDL_GetError() << std::endl;
			return;
		}
	}

	WindowSystem::~WindowSystem()
	{
		if (window_)
		{
			SDL_DestroyWindow(window_);
		}
		SDL_Quit();
	}
}


