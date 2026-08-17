#include "SceneSystem.h"

namespace VS
{
	SceneSystem::SceneSystem(InputSystem* input_system, FrameContext* context)
		:context_(context), input_system_(input_system)
	{}

	void SceneSystem::Update(float dt)
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
			for (size_t i = 0; i < 10000; i++)
			{
				SDL_FRect dst_rect = { 100, 100, 50, 50 };
				res->dst_rect.push_back(dst_rect);
			}

			res->dst_rect.emplace_back(x, 200, 50, 50);
			//std::this_thread::sleep_for(std::chrono::microseconds(200));

			context_->AddReadyResource(res);
		}
	}
}