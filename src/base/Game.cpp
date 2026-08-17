#include "Game.h"

#include "render/RenderSystem.h"
#include "render/WindowSystem.h"
#include "InputSystem.h"

#include <thread>

#include <SDL3/SDL.h>
#include <spdlog/spdlog.h>

namespace VS
{
	Game::Game()
        :frame_count_(0), elapsed_(0.0f)
	{
        window_system_ = std::make_unique<WindowSystem>();
        frame_context_ = std::make_unique<FrameContext>();
        input_system_ = std::make_unique<InputSystem>();
        render_system_ = std::make_unique<RenderSystem>(window_system_.get(), frame_context_.get());
        scene_system_ = std::make_unique<SceneSystem>(input_system_.get(), frame_context_.get());
	}
	
	Game::~Game()
	{
        render_system_.reset();
        window_system_.reset();
	}

    void Game::Run()
    {
        std::thread logic_thread = std::thread(&Game::LogicUpdate, this);

        while (isRunning) {
            RenderUpdate();
            InputUpdate();
        }

        logic_thread.join();
    }

    void Game::InputUpdate()
    {
        input_system_->Update();

        if (input_system_->IsQuit())
        {
            isRunning = false;
            frame_context_->Stop();
        }
    }

    void Game::LogicUpdate()
    {
        // TODO: redesign synchronization
        while (isRunning)
        {
            float dt = logic_timer_.Elapsed();
            logic_timer_.Reset();
            scene_system_->Update(dt);
        }
    }

    void Game::RenderUpdate()
    {
        CalcFPS();
        render_system_->Update();
    }

    void Game::CalcFPS()
    {
        float dt = render_timer_.Elapsed();
        render_timer_.Reset();

        frame_count_++;
        elapsed_ += dt;

        if (elapsed_ >= 1.0f)
        {
            spdlog::info("FPS: {}", frame_count_ / elapsed_);
            frame_count_ = 0;
            elapsed_ = 0;
        }
    }
}


