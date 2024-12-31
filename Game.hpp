#include <iostream>
#include <SDL.h>
#include <vector>
#include "GameEngine.hpp"
#include "Paddle.hpp"
#include "Bullet.hpp"
#include "Ball.hpp"
#ifndef GAME_HPP
#define GAME_HPP




// I will use this class for all high level entities in the game

class Game : public GameEngine {
private:
	std::vector<std::unique_ptr<Paddle>> m_Paddles;
	std::vector<std::unique_ptr<Bullet>> m_Bullets;
	std::unique_ptr<Ball> m_Ball; // 1 ball for now
	Uint32 lastBulletTime = 0; // tracking the last time a bullet was fired
	int cooldown = 0; // cooldown time in milliseconds

	Uint32 lastAIBulletTime = 0;
	int aicooldown = 0;
public:

	void SetCoolDown(int Cooldown) {
		this->cooldown = Cooldown;
	}

	~Game() {
		std::cout << "Game has been destroyed!" << std::endl;
	}

	void LoadAssets(std::unique_ptr<Game>& game, std::vector<std::unique_ptr<Ball>>& v1);
	void MakePaddle(int PlayerX, int PlayerY, int Player_Width, int Player_Height);
	void MakeBullet(int PlayerX, int PlayerY, int Player_Width, int Player_Height);
	std::unique_ptr<Ball> MakeBall(int PlayerX, int PlayerY, int Player_Width, int Player_Height);
	void RemoveBullet(int index);
	Paddle* GetPaddle(int i);
	void HandleInput(std::unique_ptr<Game>& game, SDL_Event e,
		bool& running, const Uint8* keyboardState, SDL_Renderer* renderer);
	void Render(SDL_Renderer* renderer);
	void HandleAI(int paddlenum, SDL_Renderer* renderer);
};

#endif