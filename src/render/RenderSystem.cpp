#include "RenderSystem.h"

#include "WindowSystem.h"

#include <iostream>

#include <SDL3/SDL.h>

namespace VS
{
	RenderSystem::RenderSystem(const WindowSystem& window_system, FrameContext* context)
		:renderer_(nullptr), context_(context)
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
		FrameResource& res = context_->GetRenderFrameResource();

		SDL_SetRenderDrawColor(renderer_, 30, 30, 50, 255);
		SDL_RenderClear(renderer_);

		SDL_SetRenderDrawColor(renderer_, 255, 34, 100, 255);
		for (size_t i = 0; i < res.sprites.size(); i++)
		{
			SDL_RenderFillRect(renderer_, &res.sprites[i]);
		}

		SDL_RenderPresent(renderer_);
	}
}

