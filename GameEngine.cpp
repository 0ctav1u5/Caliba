#include <iostream>
#include <SDL.h>
#include <memory>
#include <vector>
#include "GameEngine.hpp"
#include "Paddle.hpp"
#include "Bullet.hpp"
#include "Ball.hpp"
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




// note - we have to create at least two paddles for this code to function
// i will soon implement functionality which handles <2 paddles


void GameEngine::GameLoop() {
    bool running = true;

    // Game -- Handles game events
    std::unique_ptr<Game> game = std::make_unique<Game>();

    game->LoadAssets(game);

    SDL_Event e; // for handling keyboard events
    const Uint8* keyboardState = SDL_GetKeyboardState(nullptr); // checks state to prevent lag

    // for controlling frame rate
    const int FPS = 60, FrameDelay = 1000 / FPS;
    Uint32 FrameStart = 0;
    int FrameTime = 0;

    // GAME LOOP

    while (running) {
        FrameStart = SDL_GetTicks();
        game->SetCoolDown(500); // cooldown can be changed at will
        game->SetEnemyCooldown(400);
        while (SDL_PollEvent(&e) != 0) { // 0 = no events to be processed
            game->HandleInput(game, e, running, keyboardState, renderer); // player input
        }

        // Handle AI for chosen paddle -- this will be changed with levels
        game->HandleAI(1, renderer);

        // Clear the screen and render background
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Black background
        SDL_RenderClear(renderer);

        // Render game objects
        game->Render(renderer);

        // Update the screen
        SDL_RenderPresent(renderer);

        // Control the frame rate
        FrameTime = SDL_GetTicks() - FrameStart;
        if (FrameDelay > FrameTime) {
            SDL_Delay(FrameDelay - FrameTime); // Delay to maintain constant FPS
        }
        if ((game->GetPaddle(0)->GetHP() <= 0) || (game->GetPaddle(1)->GetHP() <= 0)) {
            running = false;
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