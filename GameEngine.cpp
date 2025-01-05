#include <iostream>
#include <SDL.h>
#include <memory>
#include <vector>
#include <random>
#include "GameEngine.hpp"
#include "Paddle.hpp"
#include "Bullet.hpp"
#include "Ball.hpp"
#include "Game.hpp"

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
    game = std::make_unique<Game>();
    if (!game->LoadAssets()) {
        Cleanup("Error. Failed to load game assets!");
        return false;
    }
    return true;
}


void GameEngine::GameLoop() {
    bool running = true;

    SDL_Event e; // for handling my keyboard events
    const Uint8* keyboardState = SDL_GetKeyboardState(nullptr); // checks state to prevent lag

    // for controlling frame rate
    const int FPS = 60, FrameDelay = 1000 / FPS;
    Uint32 FrameStart = 0;
    int FrameTime = 0;

    // GAME LOOP

    while (running) {
        FrameStart = SDL_GetTicks();
        game->SetCoolDown(500); // cooldown for bullet rate, increase for slower bullet production
        game->SetEnemyCooldown(600);
        while (SDL_PollEvent(&e) != 0) { // 0 = no events to be processed
            game->HandleInput(game, e, running, keyboardState, renderer, m_WINDOW_WIDTH, m_WINDOW_HEIGHT); // player input
        }

        // Handle AI for chosen paddle -- this will be changed with levels
        game->HandleAI(1, 0, renderer, m_WINDOW_WIDTH, m_WINDOW_HEIGHT);

        DrawBackground();

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

void GameEngine::DrawBackground() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // RGB for black
    SDL_RenderClear(renderer); // Clear the screen with black

    static std::vector<SDL_Point> stars; // vector of SDL points (SDL points are stored
    // (like this {x, y} so vector would look like {{x, y}, {x, y}...}

    // Only generate stars once
    if (stars.empty()) { // if vector is empty then
        std::random_device rd;
        std::mt19937 gen(rd()); // random seed generator
        std::uniform_int_distribution<int> distX(0, m_WINDOW_WIDTH); // 0-500
        std::uniform_int_distribution<int> distY(0, m_WINDOW_HEIGHT); // 0-500

        // Constant number of starts
        const int NUM_STARS = 150;
        for (int i = 0; i < NUM_STARS; ++i) {
            SDL_Point star = { distX(gen), distY(gen) }; // x = 0-500, y = 0-500;
            // starts are plotted sporadically at random locations 150 times
            stars.push_back(star); // pushes all stars to the back of the vector
        }
    }

    // Set the drawing color for stars
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    // Draw all the stars
    for (const auto& star : stars) { // for each loop for looping through vector
        SDL_RenderDrawPoint(renderer, star.x, star.y); // {x, y} are SDL points
    }
}

const int GameEngine::GetWindowWidth() {
    return m_WINDOW_WIDTH;
}
const int GameEngine::GetWindowHeight() {
    return m_WINDOW_HEIGHT;
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