#pragma once

class SDL_Renderer;

namespace VS
{
	class WindowSystem;

	class RenderSystem
	{
	public:
		RenderSystem(const WindowSystem& window_system);
		~RenderSystem();

		void Update(float dt);

	private:
		SDL_Renderer* renderer_;
	};
}