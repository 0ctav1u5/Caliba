#include <iostream>
#include <SDL.h>
#include "GameEngine.hpp"
#include "Paddle.hpp"
#ifndef GAME_HPP
#define GAME_HPP




// I will use this class for all high level entities in the game

class Game : public GameEngine {
private:
	std::unique_ptr<Paddle> m_player;
public:

	Game() {
		m_player = std::make_unique<Paddle>(200, 485, 100, 10);
		m_player->SetColour(0, 0, 255); // Set the paddle color
	}

	~Game() {
		std::cout << "Game has been destroyed!" << std::endl;
	}

	void MakePaddle(int PlayerX, int PlayerY, int Player_Width, int Player_Height);
	const std::unique_ptr<Paddle>& GetPlayer() const;
	void HandleInput(std::unique_ptr<Game>& game, SDL_Event e,
		bool& running, const Uint8* keyboardState);
};

#endif