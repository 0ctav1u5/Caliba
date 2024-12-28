#include <iostream>
#include <SDL.h>
#include <memory>
#include "Game.hpp"
#include "Paddle.hpp"


void Game::Render() {
    if (!m_Paddles.empty()) {
        for (auto& paddle : m_Paddles) {
            paddle->RenderPaddle(GetRenderer());
        }
    }
}

void Game::MakePaddle(int PlayerX, int PlayerY, int Player_Width, int Player_Height) {
    auto paddle = std::make_unique<Paddle>
        (PlayerX, PlayerY, Player_Width, Player_Height);
    paddle->SetColour(0, 0, 255); // Sets the colour of the paddle to blue
    m_Paddles.push_back(std::move(paddle));
}

const std::vector<std::unique_ptr<Paddle>>& Game::GetPaddles() const {
    return m_Paddles;
}

void Game::HandleInput(std::unique_ptr<Game>& game, SDL_Event e,
    bool& running, const Uint8* keyboardState) {
    if (e.type == SDL_QUIT || (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)) {
        running = false;
    }
        if (keyboardState[SDL_SCANCODE_LEFT]) { // Check if LEFT arrow is held
            if (m_Paddles[0]->GetX() >= 10) { // Ensure paddle doesn't move off-screen
                m_Paddles[0]->Move(-10, 0);
            }
        }
        if (keyboardState[SDL_SCANCODE_RIGHT]) { // Check if RIGHT arrow is held
            if (m_Paddles[0]->GetX() + m_Paddles[0]->GetWidth() < GetWindowWidth()) { // Ensure paddle stays within bounds
                m_Paddles[0]->Move(10, 0);
            }
        }
}