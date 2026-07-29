#include "Game.h"

#include "render/RenderSystem.h"
#include "render/WindowSystem.h"

#include <iostream>
#include <thread>

#include <SDL3/SDL.h>

namespace VS
{
	Game::Game()
	{
        window_system_ = std::make_unique<WindowSystem>();
        render_system_ = std::make_unique<RenderSystem>(*window_system_);
	}
	
	Game::~Game()
	{
        render_system_.reset();
        window_system_.reset();
	}

    void Game::Run()
    {
        std::thread logic_thread = std::thread(&Game::LogicUpdate, this, 0);

        SDL_Event event;
        while (isRunning) {
            // Move to InputSystem
            while (SDL_PollEvent(&event)) {
                if (event.type == SDL_EVENT_QUIT) {
                    isRunning = false;
                }
            }

            RenderUpdate(0);
        }

        logic_thread.join();
    }

    void Game::LogicUpdate(float dt)
    {
        while (isRunning)
        {
            std::cout << "Logic" << std::endl;
        }
    }

    void Game::RenderUpdate(float dt)
    {
        render_system_->Update(dt);
        std::cout << "Render" << std::endl;
    }
}


