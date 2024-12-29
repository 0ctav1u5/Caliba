#include <iostream>
#include <SDL.h>
#include <vector>
#include "GameEngine.hpp"
#include "Paddle.hpp"
#ifndef GAME_HPP
#define GAME_HPP




// I will use this class for all high level entities in the game

class Game : public GameEngine {
private:
	std::vector<std::unique_ptr<Paddle>> m_Paddles;
public:

	Game() {}

	~Game() {
		std::cout << "Game has been destroyed!" << std::endl;
	}

	void MakePaddle(int PlayerX, int PlayerY, int Player_Width, int Player_Height);
	Paddle* GetPaddle(int i);
	void HandleInput(std::unique_ptr<Game>& game, SDL_Event e,
	bool& running, const Uint8* keyboardState);
	void Render();


	void HandleAI(int paddlenum); // handles AI
};

#endif