#pragma once

#include "FrameContext.h"

class SDL_Renderer;

namespace VS
{
	class WindowSystem;

	class RenderSystem
	{
	public:
		RenderSystem(const WindowSystem& window_system, FrameContext* context);
		~RenderSystem();

		void Update(float dt);

	private:
		SDL_Renderer* renderer_;
		FrameContext* context_;
	};
}