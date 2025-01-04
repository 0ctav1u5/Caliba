#ifndef GAME_HPP
#define GAME_HPP

#include <SDL.h>
#include <vector>
#include <memory>
#include "Paddle.hpp"
#include "Bullet.hpp"
#include "Ball.hpp"

// I will use this class for all high level entities in the game

class Game {
private:
	std::vector<std::unique_ptr<Paddle>> m_Paddles;
	std::vector<std::unique_ptr<Bullet>> m_Bullets;
	std::vector < std::unique_ptr<Bullet>> m_EnemyBullets;
	std::vector<std::unique_ptr<Ball>> m_Balls; 
	Uint32 lastBulletTime = 0; // tracking the last time a bullet was fired
	int cooldown = 0; // cooldown time in milliseconds

	Uint32 lastEnemyBulletTime = 0;
	int enemycooldown = 0;
public:

	void SetCoolDown(int Cooldown) {
		this->cooldown = Cooldown;
	}

	void SetEnemyCooldown(int cooldown) {
		this->enemycooldown = cooldown;
	}

	~Game() {
		std::cout << "Game has been destroyed!" << std::endl;
	}
	void Render(SDL_Renderer* renderer);
	bool LoadAssets();
	void MakePaddle(int PlayerX, int PlayerY, int Player_Width, int Player_Height);
	void MakeBullet(int PlayerX, int PlayerY, int Player_Width, int Player_Height);
	void MakeEnemyBullet(int PlayerX, int PlayerY, int Player_Width, int Player_Height);
	void MakeBall(int PlayerX, int PlayerY, int Player_Width);
	void RemoveBullet(int index);
	Paddle* GetPaddle(int i);
	Ball* GetBall(int i);
	void HandleInput(std::unique_ptr<Game>& game, SDL_Event e,
		bool& running, const Uint8* keyboardState, SDL_Renderer* renderer,
		const int Window_Width, const int Window_Height);
	void HandleAI(int paddlenum, int ballnum, SDL_Renderer* renderer, const int m_WINDOW_WIDTH,
		const int m_WINDOW_HEIGHT);
};

#endif