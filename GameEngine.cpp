#include <iostream>
#include <SDL.h>
#include <memory>
#include "GameEngine.hpp"
#include "Paddle.hpp"
#include "Bullet.hpp"
#include "Game.hpp"

int HP = 100;

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
    int PlayerX = 200, PlayerY = 485, PlayerWidth = 100, PlayerHeight = 10;

    // Game -- Handles game events
    std::unique_ptr<Game> game = std::make_unique<Game>();

    // PLAYER PADDLE
    game->MakePaddle(PlayerX, PlayerY, PlayerWidth, PlayerHeight);

    // AI PADDLE
    game->MakePaddle(PlayerX, PlayerY - 480, PlayerWidth, PlayerHeight);
    game->GetPaddle(1)->SetColour(255, 0, 0);

    SDL_Event e;
    const Uint8* keyboardState = SDL_GetKeyboardState(nullptr); // checks state to prevent lag

    const int FPS = 60;
    const int FrameDelay = 1000 / FPS;
    Uint32 FrameStart = 0;
    int FrameTime = 0;

    while (running) {
        FrameStart = SDL_GetTicks();
        while (SDL_PollEvent(&e) != 0) { // 0 = no events to be processed
            game->SetCoolDown(300); // cooldown can be changed at will
            game->HandleInput(game, e, running, keyboardState, renderer); // player input
        }

        // Handle AI for chosen paddle
        game->HandleAI(1);

        // Clear the screen and render everything
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Black background
        SDL_RenderClear(renderer);

        // Render paddles
        game->GetPaddle(0)->RenderPaddle(renderer);
        game->GetPaddle(1)->RenderPaddle(renderer);


        
        // Render bullets
        // How this works: 
        for (int i = 0; i < game->GetBulletCount(); ++i) {
            Bullet* bullet = game->GetBullet(i); // Use GetBullet() to access each bullet
            int paddleY = game->GetPaddle(1)->GetY();
            int bulletY = bullet->GetY();
            int paddleX = game->GetPaddle(1)->GetX();
            int paddleWidth = game->GetPaddle(1)->GetWidth();
            int bulletX = bullet->GetX();
            int paddleHeightfromTop = (paddleY + game->GetPaddle(1)->GetHeight());

            if (bullet) {
                bullet->Move(0, -5);  // Move bullet upwards
                bullet->RenderBullet(renderer);
            }
            if (bulletY <= paddleY) {
                game->RemoveBullet(i);
                --i;
                continue;
            }
            if (bulletY <= paddleHeightfromTop && ((bulletX >= paddleX) && (bulletX <= (paddleX + paddleWidth)))) {
                HP -= 10;
                std::cout << "Hit!" << " HP: " << HP << std::endl;
                game->RemoveBullet(i);
            }
            if (HP <= 0) {
                running = false;
            }
        }
        // Update the screen
        SDL_RenderPresent(renderer);

        // Control the frame rate
        FrameTime = SDL_GetTicks() - FrameStart;
        if (FrameDelay > FrameTime) {
            SDL_Delay(FrameDelay - FrameTime); // Delay to maintain constant FPS
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