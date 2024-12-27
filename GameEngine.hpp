#include <iostream>
#include <SDL.h>
#ifndef GAME_ENGINE_HPP
#define GAME_ENGINE_HPP




// I will use this class for handling all the low level functionality behind the scenes

class GameEngine {
private:
	const int m_WINDOW_HEIGHT = 500;
	const int m_WINDOW_WIDTH = 500;
	const char* m_WINDOW_NAME = "Caliba";
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
public:

	virtual ~GameEngine(){
		std::cout << "GameEngine has been destroyed!" << std::endl;
		SDL_DestroyWindow(window);
		SDL_Quit();
	}

	bool Initialise();
	void GameLoop();

};

#endif