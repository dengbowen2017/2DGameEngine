#include "RenderSystem.h"

#include "WindowSystem.h"

#include <iostream>

#include <SDL3/SDL.h>

namespace VS
{
	RenderSystem::RenderSystem(const WindowSystem& window_system)
		:renderer_(nullptr)
	{
		renderer_ = SDL_CreateRenderer(window_system.GetWindowHandle(), nullptr);
		if (!renderer_)
		{
			std::cerr << "Failed to create SDL_Renderer: " << SDL_GetError() << std::endl;
			return;
		}
	}

	RenderSystem::~RenderSystem()
	{
		if (renderer_)
		{
			SDL_DestroyRenderer(renderer_);
		}
	}

	void RenderSystem::Update(float dt)
	{
		SDL_SetRenderDrawColor(renderer_, 30, 30, 50, 255);
		SDL_RenderClear(renderer_);

		SDL_RenderPresent(renderer_);
	}
}

