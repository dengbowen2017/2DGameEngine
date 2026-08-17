#pragma once

#include <thread>
#include <chrono>

#include "render/FrameContext.h"

#include "base/InputSystem.h"
#include "base/Timer.h"

namespace VS
{
	class SceneSystem
	{
	public:
		SceneSystem(InputSystem* input_system, FrameContext* context);
		void Update(float dt);

	private:
		InputSystem* input_system_;
		FrameContext* context_;

		float x = 100.f;
	};
}