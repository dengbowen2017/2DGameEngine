#pragma once

#include <memory>
#include <chrono>

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
		void LogicUpdate();
		void RenderUpdate();
		
		float CalcDeltaTime(std::chrono::steady_clock::time_point& last_time);

	private:
		std::unique_ptr<RenderSystem> render_system_;
		std::unique_ptr<WindowSystem> window_system_;
		std::unique_ptr<SceneSystem> scene_system_;
		std::unique_ptr<FrameContext> frame_context_;

		std::chrono::steady_clock::time_point last_logic_update_time_;
		std::chrono::steady_clock::time_point last_render_update_time_;
		bool isRunning = true;
	};
}