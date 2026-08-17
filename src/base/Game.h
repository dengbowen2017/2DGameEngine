#pragma once

#include <memory>
#include <chrono>

#include "render/FrameContext.h"
#include "scene/SceneSystem.h"
#include "base/Timer.h"

namespace VS
{
	class RenderSystem;
	class WindowSystem;
	class InputSystem;

	class Game
	{
	public:
		Game();
		~Game();

		void Run();

	private:
		void InputUpdate();
		void LogicUpdate();
		void RenderUpdate();
		
		void CalcFPS();

	private:
		std::unique_ptr<RenderSystem> render_system_;
		std::unique_ptr<WindowSystem> window_system_;
		std::unique_ptr<SceneSystem> scene_system_;
		std::unique_ptr<FrameContext> frame_context_;
		std::unique_ptr<InputSystem> input_system_;

		bool isRunning = true;

		Timer logic_timer_;
		Timer render_timer_;
		int frame_count_;
		float elapsed_;
	};
}