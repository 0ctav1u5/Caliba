#include <iostream>
#include <SDL.h>
#include <vector>
#include "GameEngine.hpp"
#include "Paddle.hpp"
#include "Bullet.hpp"
#ifndef GAME_HPP
#define GAME_HPP




// I will use this class for all high level entities in the game

class Game : public GameEngine {
private:
	std::vector<std::unique_ptr<Paddle>> m_Paddles;
	std::vector<std::unique_ptr<Bullet>> m_Bullets;
	Uint32 lastBulletTime = 0; // tracking the last time a bullet was fired
	int cooldown; // cooldown time in milliseconds
public:



	void SetLastBulletTime(Uint32 lastbulletime) {
		this->lastBulletTime = lastbulletime;
	}

	void SetCoolDown(int Cooldown) {
		this->cooldown = Cooldown;
	}



	~Game() {
		std::cout << "Game has been destroyed!" << std::endl;
	}

	void MakePaddle(int PlayerX, int PlayerY, int Player_Width, int Player_Height);
	void MakeBullet(int PlayerX, int PlayerY, int Player_Width, int Player_Height);
	Paddle* GetPaddle(int i);
	Bullet* GetBullet(int i);
	void HandleInput(std::unique_ptr<Game>& game, SDL_Event e,
		bool& running, const Uint8* keyboardState, SDL_Renderer* renderer);
	void Render();
	void HandleAI(int paddlenum); // handles AI
	int GetBulletCount() const;
};

#endif