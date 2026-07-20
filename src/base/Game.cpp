#include "Game.h"

#include "render/RenderSystem.h"
#include "render/WindowSystem.h"

#include <iostream>

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
        SDL_Event event;

        while (isRunning) {
            // Move to InputSystem
            while (SDL_PollEvent(&event)) {
                if (event.type == SDL_EVENT_QUIT) {
                    isRunning = false;
                }
            }

            LogicUpdate(0);
            RenderUpdate(0);
        }
    }

    void Game::LogicUpdate(float dt)
    {

    }

    void Game::RenderUpdate(float dt)
    {
        render_system_->Update(dt);
    }
}


