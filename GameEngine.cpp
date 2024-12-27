#include <iostream>
#include <SDL.h>
#include <memory>
#include "GameEngine.hpp"
#include "Paddle.hpp"

// boilerplate code for initialising framework, creating window and renderer
bool GameEngine::Initialise() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "Error. Failed to initialise!" << std::endl;
        return false;
    }

    window = SDL_CreateWindow(m_WINDOW_NAME, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        m_WINDOW_WIDTH, m_WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window) {
        std::cerr << "Error. Failed to create a window!" << std::endl;
        SDL_Quit();
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer) {
        std::cerr << "Error. Graphics could not be rendered!" << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return false;
    }

    return true;
}

void GameEngine::GameLoop() {
    bool running = true;
    int PlayerX = 200, PlayerY = 485;
    const int Player_Width = 100, Player_Height = 10;

    // PLAYER
    std::unique_ptr<Paddle> player = std::make_unique<Paddle>
        (PlayerX, PlayerY, Player_Width, Player_Height);
    player->SetColour(0, 0, 255); // Sets the colour of the paddle to be blue
    
    
    SDL_Event e;
    const Uint8* keyboardState = SDL_GetKeyboardState(nullptr); // checks state to prevent lag

    while (running) {
        while (SDL_PollEvent(&e) != 0) { // 0 = no events to be processed
            if (e.type == SDL_QUIT) {
                running = false;
            }
            else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE) {
                running = false;
            }

            if (keyboardState[SDL_SCANCODE_LEFT]) { // Check if LEFT arrow is held
                if (player->GetX() >= 10) { // Ensure paddle doesn't move off-screen
                    player->Move(-10, 0);
                }
            }
            if (keyboardState[SDL_SCANCODE_RIGHT]) { // Check if RIGHT arrow is held
                if (player->GetX() + player->GetWidth() < m_WINDOW_WIDTH) { // Ensure paddle stays within bounds
                    player->Move(10, 0);
                }
            }               
        }
        // BACKGROUND
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // R G B, Opaqueness
        SDL_RenderClear(renderer);                     // Clear the renderer once per frame


        player->RenderPaddle(renderer); // Renders the player


        SDL_RenderPresent(renderer); // Initial setup of background and paddle
    }
}

