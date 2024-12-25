#include <iostream>
#include <SDL.h>
#include "GameEngine.hpp"
#ifndef GAME_HPP
#define GAME_HPP




// I will use this class for all high level entities in the game

class Game : public GameEngine {
private:
public:


	~Game() {
		std::cout << "Game has been destroyed!" << std::endl;
	}
};

#endif