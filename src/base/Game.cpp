#include "Game.h"

#include <iostream>

#include <SDL3/SDL.h>

namespace VS
{
	Game::Game()
        :window_(nullptr), renderer_(nullptr)
	{
	    if (!SDL_Init(SDL_INIT_VIDEO)) {
            std::cerr << "Failed to init SDL: " << SDL_GetError() << std::endl;
            return;
        }

        if (!SDL_CreateWindowAndRenderer("2D Game Engine", 800, 600, 0, &window_, &renderer_)) {
            std::cerr << "Failed to create window and render: " << SDL_GetError() << std::endl;
            SDL_Quit();
            return;
        }
	}
	
	Game::~Game()
	{
        SDL_DestroyRenderer(renderer_);
        SDL_DestroyWindow(window_);
        SDL_Quit();
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
        SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 255);
        SDL_RenderClear(renderer_);

        SDL_RenderPresent(renderer_);
    }
}


