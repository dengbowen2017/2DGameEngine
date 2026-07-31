#pragma once

#include <memory>

#include <thread>

#include "render/FrameContext.h"
#include "scene/SceneSystem.h"

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
		std::unique_ptr<SceneSystem> scene_system_;
		std::unique_ptr<FrameContext> render_context_;

		bool isRunning = true;

		std::thread logic_thread;
	};
}