#include <iostream>
#include <string>
#include <random>
#include <memory>
#include <vector>
#include <windows.h>
#include <fstream>
#include <chrono>
#include <thread>
#include <SDL.h>
#include "GameEngine.hpp"
#include "Game.hpp"

int main(int argc, char* argv[]) {

    // smart pointer because I don't want to worry about freeing memory
    std::unique_ptr<GameEngine> game = std::make_unique<Game>();
    if (!game->Initialise()) {
        std::cerr << "Game Engine could not be initialised!" << std::endl;
        return -1;
    }
    game->GameLoop();
    return 0;
}