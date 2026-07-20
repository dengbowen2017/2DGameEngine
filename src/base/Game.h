#pragma once

class SDL_Window;
class SDL_Renderer;

namespace VS
{
	class Game
	{
	public:
		Game();
		~Game();

		void Run();

	private:
		void LogicUpdate(float dt);
		void RenderUpdate(float dt);

	private:
		SDL_Window* window_;
		SDL_Renderer* renderer_;

		bool isRunning = true;
	};
}