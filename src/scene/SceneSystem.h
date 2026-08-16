#pragma once

#include <thread>
#include <chrono>

#include "render/FrameContext.h"

#include "base/input/InputSystem.h"
#include "base/timer/Timer.h"

namespace VS
{
	class SceneSystem
	{
	public:
		SceneSystem(InputSystem* input_system, FrameContext* context)
			:context_(context), input_system_(input_system)
		{}

		void Update(float dt)
		{
			if (input_system_->GetKey("A"))
			{
				x -= 500.f * dt;
			}

			if (input_system_->GetKey("D"))
			{
				x += 500.f * dt;
			}

			FrameResource* res = context_->GetEmptyResource();
			if (res)
			{
				PROFILE_SCOPE("PrepareRects");
				for (size_t i = 0; i < 5000; i++)
				{
					SDL_FRect dst_rect = { 100, 100, 50, 50 };
					res->dst_rect.push_back(dst_rect);
				}

				res->dst_rect.emplace_back(x, 200, 50, 50);

				context_->AddReadyResource(res);
			}
		}

	private:
		InputSystem* input_system_;
		FrameContext* context_;

		float x = 100.f;
	};
}