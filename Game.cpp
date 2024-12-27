#include <iostream>
#include <SDL.h>
#include <memory>
#include "Game.hpp"
#include "Paddle.hpp"


void Game::MakePaddle(int PlayerX, int PlayerY, int Player_Width, int Player_Height) {
    std::unique_ptr<Paddle> player = std::make_unique<Paddle>
        (PlayerX, PlayerY, Player_Width, Player_Height);
    player->SetColour(0, 0, 255); // Sets the colour of the paddle to blue
}

const std::unique_ptr<Paddle>& Game::GetPlayer() const {
    return m_player;
}

void Game::HandleInput(std::unique_ptr<Game>& game, SDL_Event e,
    bool& running, const Uint8* keyboardState) {
    if (e.type == SDL_QUIT || (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)) {
        running = false;
    }
    if (keyboardState[SDL_SCANCODE_LEFT]) { // Check if LEFT arrow is held
        if (m_player->GetX() >= 10) { // Ensure paddle doesn't move off-screen
            m_player->Move(-10, 0);
        }
    }
    if (keyboardState[SDL_SCANCODE_RIGHT]) { // Check if RIGHT arrow is held
        if (m_player->GetX() + m_player->GetWidth() < GetWindowWidth()) { // Ensure paddle stays within bounds
            m_player->Move(10, 0);
        }
    }
}