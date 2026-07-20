#pragma once

class SDL_Window;

namespace VS
{
	class WindowSystem
	{
	public:
		WindowSystem();
		~WindowSystem();

		SDL_Window* GetWindowHandle() const { return window_; }

	private:
		SDL_Window* window_;
	};
}