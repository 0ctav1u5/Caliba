#include <iostream>
#include <SDL.h>
#include <memory>
#include <random>
#include "Game.hpp"
#include "Paddle.hpp"
#include "Bullet.hpp"

void Game::Render() {
    if (!m_Paddles.empty()) {
        for (auto& paddle : m_Paddles) { // renders all paddles in the paddle vector
            paddle->RenderPaddle(GetRenderer());
        }
    }

    if (!m_Bullets.empty()) {
        for (auto& bullet : m_Bullets) { // renders all bullets in the bullets vector
            bullet->RenderBullet(GetRenderer()); 
        }
    }
}

void Game::MakePaddle(int PlayerX, int PlayerY, int Player_Width, int Player_Height) {
    auto paddle = std::make_unique<Paddle> // dynamically stored object (not pointer)
        (PlayerX, PlayerY, Player_Width, Player_Height);
    paddle->SetColour(0, 0, 255); // default colour of all paddles is blue
    m_Paddles.push_back(std::move(paddle)); // stores new paddle on the vector
}

void Game::MakeBullet(int PlayerX, int PlayerY, int Player_Width, int Player_Height) {
    auto bullet = std::make_unique<Bullet> // dynamically stored object (not pointer)
        (PlayerX, PlayerY, Player_Width, Player_Height);
    bullet->SetColour(0, 255, 0); // default colour of all paddles is blue
    m_Bullets.push_back(std::move(bullet)); // stores new paddle on the vector
}

void Game::RemoveBullet(int index) {
    if (index >= 0 && index < m_Bullets.size()) {
        m_Bullets.erase(m_Bullets.begin() + index); // Removes the bullet from the vector
    }
}

Paddle* Game::GetPaddle(int i) {
    if (i >= 0 && i < m_Paddles.size()) {
        return m_Paddles[i].get();  // return raw pointer to the paddle
    }
    return nullptr;  // Return nullptr if index is out of bounds
}

Bullet* Game::GetBullet(int i) {
    if (i >= 0 && i < m_Bullets.size()) {
        return m_Bullets[i].get();  // Return raw pointer to the bullet
    }
    return nullptr;  // Return nullptr if index is out of bounds
}

int Game::GetBulletCount() const {
    return m_Bullets.size();  // Return the number of bullets
}

void Game::HandleInput(std::unique_ptr<Game>& game, SDL_Event e,
    bool& running, const Uint8* keyboardState, SDL_Renderer* renderer) {
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
    Uint32 currentTime = SDL_GetTicks(); // gets current game time since SDL_init was called

    // how does the maths work?
    // e.g. difference: newtime(5000) - oldtime(4500), we know that 500 has passed, therefore we
    // can test against cooldown (300 for instance), being as 500 is greater than
    // cooldown, enough time has passed


    if (keyboardState[SDL_SCANCODE_UP] && (currentTime - this->lastBulletTime) >= cooldown) {
        int paddleX = m_Paddles[0]->GetX(); // gets x coords of the player's paddle
        int paddleY = m_Paddles[0]->GetY(); // gets y coords of the player's paddle
        int paddleWidth = m_Paddles[0]->GetWidth(); // width needed as well to centre bullet

        // Creates a new bullet each time the up key is pressed, slightly above the player's paddle
        MakeBullet(paddleX + paddleWidth / 2 - 1, paddleY - 13, 3, 13);
        lastBulletTime = currentTime; // sets currentTime to new oldtime
    }
}

// paddlenum will be whatever paddle we wish to handle stored in the vector
void Game::HandleAI(int paddlenum) {
    static int direction = 1;  // starts the direction to right
    // needs to be static as the memory needs to be remembered outside of scope

    int speed = 5;           // Paddle speed per frame

    // Get the current paddle position
    int paddleX = m_Paddles[paddlenum]->GetX();
    int paddleWidth = m_Paddles[paddlenum]->GetWidth();

    // Reverse direction if paddle hits the screen edges
    if (paddleX <= 0) { // if x is 0, then the paddle is the furthest point left
        direction = 1; // move paddle right
    }
    else if (paddleX + paddleWidth >= GetWindowWidth()) { // windowWidth is the furthers point right
        direction = -1; // move paddle left
    }

    // direction is either 1 (right) or -1 (left) and the speed is how quickly it moves
    m_Paddles[paddlenum]->Move(direction * speed, 0); // (5, 0) moves 5 right per frame
    // notice how the coords are (x, 0) because x is being changed
}