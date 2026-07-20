#pragma once

#include <memory>

namespace VS
{
	class RenderSystem;
	class WindowSystem;

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
		std::unique_ptr<RenderSystem> render_system_;
		std::unique_ptr<WindowSystem> window_system_;

		bool isRunning = true;
	};
}