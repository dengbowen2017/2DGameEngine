#include "Game.h"

#include "render/RenderSystem.h"
#include "render/WindowSystem.h"

#include <iostream>
#include <thread>

#include <SDL3/SDL.h>
#include <spdlog/spdlog.h>

namespace VS
{
	Game::Game()
        :last_logic_update_time_{ std::chrono::steady_clock::now() }, 
        last_render_update_time_{ std::chrono::steady_clock::now() }
	{
        window_system_ = std::make_unique<WindowSystem>();
        frame_context_ = std::make_unique<FrameContext>();
        render_system_ = std::make_unique<RenderSystem>(*window_system_, frame_context_.get());
        scene_system_ = std::make_unique<SceneSystem>(frame_context_.get());
	}
	
	Game::~Game()
	{
        render_system_.reset();
        window_system_.reset();
	}

    void Game::Run()
    {
        std::thread logic_thread = std::thread(&Game::LogicUpdate, this);

        SDL_Event event;
        while (isRunning) {
            RenderUpdate();

            // Move to InputSystem
            while (SDL_PollEvent(&event)) {
                if (event.type == SDL_EVENT_QUIT) {
                    isRunning = false;
                    frame_context_->Stop();
                }
            }
        }

        logic_thread.join();
    }

    void Game::LogicUpdate()
    {
        while (isRunning)
        {
            float dt = CalcDeltaTime(last_logic_update_time_);
            scene_system_->Update(dt);
        }
    }

    void Game::RenderUpdate()
    {
        float dt = CalcDeltaTime(last_render_update_time_);
        spdlog::info("FPS: {}", 1 / dt);
        //std::cout << "FPS:" << 1 / dt << std::endl;
        render_system_->Update();
    }

    float Game::CalcDeltaTime(std::chrono::steady_clock::time_point& last_time)
    {
        float dt = 0;
        std::chrono::time_point now_time_point = std::chrono::steady_clock::now();
        std::chrono::duration<float> time_span = now_time_point - last_time;
        dt = time_span.count();
        last_time = now_time_point;
        return dt;
    }
}


