#include "RenderSystem.h"
#include "WindowSystem.h"

#include <iostream>
#include <SDL3/SDL.h>

#include "base/Timer.h"

namespace VS
{
	RenderSystem::RenderSystem(WindowSystem* window_system, FrameContext* context)
		:renderer_(nullptr), context_(context)
	{
		renderer_ = SDL_CreateRenderer(window_system->GetWindowHandle(), nullptr);
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

	void RenderSystem::Update()
	{
		SDL_SetRenderDrawColor(renderer_, 30, 30, 50, 255);
		SDL_RenderClear(renderer_);

		SDL_SetRenderDrawColor(renderer_, 255, 34, 100, 255);

		FrameResource* res = context_->GetReadyResource();
		if (res)
		{
			PROFILE_SCOPE("RenderRects");
			SDL_RenderFillRects(renderer_, res->dst_rect.data(), res->dst_rect.size());
			res->Clear();
			context_->AddEmptyResource(res);
		}

		SDL_RenderPresent(renderer_);
	}
}

