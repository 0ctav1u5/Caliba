#include <iostream>
#include <SDL.h>
#include <memory>
#include <vector>
#include <random>
#include "Game.hpp"
#include "Paddle.hpp"
#include "Bullet.hpp"
#include "Ball.hpp"

void Game::Render(SDL_Renderer* renderer) {
    if (!m_Paddles.empty()) {
        for (auto& paddle : m_Paddles) { // renders all paddles in the paddle vector
            paddle->RenderPaddle(renderer);
        }
    }

    if (!m_Balls.empty()) {
        for (auto& ball : m_Balls) { // renders all paddles in the paddle vector
            ball->RenderBall(renderer);
        }
    }

    if (!m_Bullets.empty()) {
        for (int i = 0; i < m_Bullets.size(); ++i) {
            Bullet* bullet = m_Bullets[i].get();  // Pointer to a vector of unique pointers

            if (bullet) {
                // Move bullet upwards (adjust 5 based on the speed of the bullet)
                bullet->Move(0, -5);

                // Render bullet -- ALL BULLETS ARE MADE IN THE RENDER FUNCTION
                bullet->RenderBullet(renderer);

                int paddleY = m_Paddles[1]->GetY(), bulletY = bullet->GetY();   // Y position of the second paddle (AI paddle)
                int paddleX = m_Paddles[1]->GetX(), paddleWidth = m_Paddles[1]->GetWidth();
                int bulletX = bullet->GetX(), paddleHeightfromTop = paddleY + m_Paddles[1]->GetHeight();

                // Check for collision with the paddle
                if (bulletY <= paddleY) {
                    // If the bullet has reached the same Y position as the paddle, then remove it
                    m_Bullets.erase(m_Bullets.begin() + i);
                    --i;  // change index because of removal
                    continue;  // no reason to keep checking this bullet so continue
                }

                // Check for a collision with the paddle area (
                if (bulletY <= paddleHeightfromTop && bulletX >= paddleX && bulletX <= paddleX + paddleWidth) {
                    m_Paddles[1]->DecreaseHP(10);
                    std::cout << "Hit! HP: " << m_Paddles[1]->GetHP() << std::endl;
                    m_Bullets.erase(m_Bullets.begin() + i);  // Remove the bullet after it hits the paddle
                    --i;  // Adjust index due to removal of the bullet
                }
            }
        }
    }

    if (!m_EnemyBullets.empty()) {
        for (int i = 0; i < m_EnemyBullets.size(); ++i) {
            Bullet* bullet = m_EnemyBullets[i].get();  // Pointer to a vector of unique pointers

            if (bullet) {
                // Move bullet upwards (adjust 5 based on the speed of the bullet)
                bullet->Move(0, 5);

                // Render bullet -- ALL BULLETS ARE MADE IN THE RENDER FUNCTION
                bullet->RenderBullet(renderer);

                int paddleY = m_Paddles[0]->GetY(), bulletY = bullet->GetY();   // Y position of the second paddle (AI paddle)
                int paddleX = m_Paddles[0]->GetX(), paddleWidth = m_Paddles[0]->GetWidth();
                int bulletX = bullet->GetX(), paddleHeightfromBottom = paddleY - m_Paddles[0]->GetHeight();

                // Check for collision with the paddle
                if (bulletY >= paddleY) {
                    // If the bullet has reached the same Y position as the paddle, then remove it
                    m_EnemyBullets.erase(m_EnemyBullets.begin() + i);
                    --i;  // change index because of removal
                    continue;  // no reason to keep checking this bullet so continue
                }

                // bulletY <= paddleHeightfromTop && bulletX >= paddleX && bulletX <= paddleX + paddleWidth
                if (bulletY >= paddleHeightfromBottom && bulletX >= paddleX && bulletX <= paddleX + paddleWidth) {
                    m_Paddles[0]->DecreaseHP(10);
                    std::cout << "Enemy Hit you! HP: " << m_Paddles[0]->GetHP() << std::endl;
                    m_EnemyBullets.erase(m_EnemyBullets.begin() + i);  // Remove the bullet after it hits the paddle
                    --i;  // Adjust index due to removal of the bullet
                }
            }
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

void Game::MakeEnemyBullet(int PlayerX, int PlayerY, int Player_Width, int Player_Height) {
    auto bullet = std::make_unique<Bullet> // dynamically stored object (not pointer)
        (PlayerX, PlayerY, Player_Width, Player_Height);
    bullet->SetColour(255, 255, 0); // default colour of all paddles is blue
    m_EnemyBullets.push_back(std::move(bullet)); // stores new paddle on the vector
}

void Game::MakeBall(int PlayerX, int PlayerY, int Player_Width, int Player_Height) {
    auto ball = std::make_unique<Ball> // dynamically stored object (not pointer)
        (PlayerX, PlayerY, Player_Width, Player_Height);
    ball->SetColour(0, 0, 255); // default colour of all balls is blue
    m_Balls.push_back(std::move(ball)); // stores new ball on the vector
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

Ball* Game::GetBall(int i) {
    if (i >= 0 && i < m_Balls.size()) {
        return m_Balls[i].get();  // return raw pointer to the paddle
    }
    return nullptr;  // Return nullptr if index is out of bounds
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

    // handles bullet creation and how long before each creation
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
void Game::HandleAI(int paddlenum, SDL_Renderer* renderer) {
    std::random_device rd;
    std::uniform_int_distribution<int> dist(1, 30);
    int randomizer = dist(rd);
    static int direction = 1;  // starts the direction to right
    int speed = 5; // Paddle speed per frame

    int paddleX = m_Paddles[paddlenum]->GetX(); // gets paddle position of specified paddle
    int paddleWidth = m_Paddles[paddlenum]->GetWidth();

    // Reverse direction if paddle hits the screen edges
    if (paddleX <= 0) { // if x is 0, then the paddle is the furthest point left
        direction = 1; // move paddle right
    }
    else if (paddleX + paddleWidth >= GetWindowWidth()) { // windowWidth is the furthers point right
        direction = -1; // move paddle left
    }

    // direction is either 1 (right) or -1 (left) and 1 x 5 is 5 or -1 x 5 is -5
    // it's a neat little trick to have a speed be involved
    if (randomizer < 30) {
        m_Paddles[paddlenum]->Move(direction * speed, 0);
    }
    else if (randomizer == 30) {
        if (direction == 1) {
            direction = -1;
            m_Paddles[paddlenum]->Move(direction * speed, 0);
        }
        else if (direction == -1) {
            direction = 1;
            m_Paddles[paddlenum]->Move(direction * speed, 0);
        }
    }
     // (5, 0) moves 5 right per frame
    // notice how the coords are (x, 0) because only x is being changed


    // LOGIC FOR ENEMY BULLETS 

    Uint32 currentTime = SDL_GetTicks();

    if ((currentTime - this->lastEnemyBulletTime) >= enemycooldown) {
        int paddleX = m_Paddles[1]->GetX(); // gets x coords of the player's paddle
        int paddleY = m_Paddles[1]->GetY(); // gets y coords of the player's paddle
        int paddleWidth = m_Paddles[1]->GetWidth(); // width needed as well to centre bullet
        // Creates a new bullet each time the up key is pressed, slightly above the player's paddle
        MakeEnemyBullet(paddleX + paddleWidth / 2 - 1, paddleY + 13, 3, 13);
        lastEnemyBulletTime = currentTime; // sets currentTime to new oldtime
    }
}


void Game::LoadAssets(std::unique_ptr<Game>& game) {
    int PlayerX = 200, PlayerY = 485, PlayerWidth = 100, PlayerHeight = 10;
    int AIX = 200, AIY = 5, AIWidth = 100, AIHeight = 10;

    // PLAYER
    game->MakePaddle(PlayerX, PlayerY, PlayerWidth, PlayerHeight);

    // AI PADDLE -- these will be changed later when levels are considered
    game->MakePaddle(AIX, AIY, AIWidth, AIHeight);
    game->GetPaddle(1)->SetColour(255, 0, 0); // needs to be set as default colour is blue

    // BALL
    game->MakeBall(250, 250, 50, 50);
    game->GetBall(0)->SetColour(140, 146, 172);
}