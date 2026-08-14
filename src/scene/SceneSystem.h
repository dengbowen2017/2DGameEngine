#pragma once

#include <thread>
#include <chrono>

#include "render/FrameContext.h"

#include "base/timer/Timer.h"

namespace VS
{
	class SceneSystem
	{
	public:
		SceneSystem(FrameContext* context)
			:context_(context)
		{}

		void Update(float dt)
		{
			FrameResource* res = context_->GetEmptyResource();
			
			if (res)
			{
				PROFILE_SCOPE("PrepareRects");

				for (size_t i = 0; i < 100000; i++)
				{
					SDL_FRect dst_rect = { 100, 100, 50, 50 };
					res->dst_rect.push_back(dst_rect);
				}

				context_->AddReadyResource(res);
			}
		}

	private:
		FrameContext* context_;
	};
}