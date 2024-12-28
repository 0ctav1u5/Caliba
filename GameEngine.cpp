#include <iostream>
#include <SDL.h>
#include <memory>
#include "GameEngine.hpp"
#include "Paddle.hpp"
#include "Game.hpp"

// boilerplate code for initialising framework, creating window and renderer
bool GameEngine::Initialise() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        Cleanup("Error. Failed to initialise!");
        return false;
    }

    window = SDL_CreateWindow(m_WINDOW_NAME, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        m_WINDOW_WIDTH, m_WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window) {
        Cleanup("Error. Failed to create a window!");
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer) {
        Cleanup("Error. Graphics could not be rendered!");
        return false;
    }

    return true;
}

void GameEngine::GameLoop() {
    bool running = true;
    int PlayerX = 200, PlayerY = 485, PlayerWidth = 100, PlayerHeight = 10;

    // Game -- Handles game events
    std::unique_ptr<Game> game = std::make_unique<Game>();

    // Player -- We can use this first paddle as our player
    game->MakePaddle(PlayerX, PlayerY, PlayerWidth, PlayerHeight);

    
    game->MakePaddle(PlayerX, PlayerY - 480, PlayerWidth, PlayerHeight);
    // default colour is blue, let's change it to red
    game->GetPaddle(1)->SetColour(255, 0, 0);
    // paddle stored at index 1 in the vector is now red

    
    
    SDL_Event e;
    const Uint8* keyboardState = SDL_GetKeyboardState(nullptr); // checks state to prevent lag

    const int FPS = 60; 
    const int FrameDelay = 1000 / FPS; // Delay per frame in milliseconds
    Uint32 FrameStart = 0;
    int FrameTime = 0;



    // PASS SDL_EVENT and std::unique_ptr<paddle> player

    while (running) {
        FrameStart = SDL_GetTicks();
        while (SDL_PollEvent(&e) != 0) { // 0 = no events to be processed
            game->HandleInput(game, e, running, keyboardState);
        }
        // BACKGROUND
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // R G B, Opaqueness
        SDL_RenderClear(renderer);                     // Clear the renderer once per frame

        // renders paddles
        game->GetPaddle(0)->RenderPaddle(renderer); 
        game->GetPaddle(1)->RenderPaddle(renderer);


        SDL_RenderPresent(renderer); // Initial setup of background and paddle


        // controlling framerate
        FrameTime = SDL_GetTicks() - FrameStart; // Time taken for the frame
        if (FrameDelay > FrameTime) {
            SDL_Delay(FrameDelay - FrameTime); // Delay to maintain pre-determined FPS
        }
    }
}

const int GameEngine::GetWindowWidth() {
    return m_WINDOW_WIDTH;
}

SDL_Renderer* GameEngine::GetRenderer() const {
    return renderer;
}

void GameEngine::Cleanup(const std::string& errormsg) {
    std::cerr << errormsg << std::endl;
    if (renderer != nullptr) {
        SDL_DestroyRenderer(renderer);  // Clean up renderer
    }
    if (window != nullptr) {
        SDL_DestroyWindow(window);
    }
    SDL_Quit();
}