#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <fstream>
#include <chrono>
#include <limits>
#include <thread>
#include <Windows.h>
#include <map>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include "MainHeader.hpp"

const int WINDOW_HEIGHT = 800; // global constants
const int WINDOW_WIDTH = 800;
const char* WINDOW_NAME = "Caliba";


// we must first initialise the framework, then create the window and finally render the graphics
// i will use main instead of SDL_Main for portability



int main(int argc, char** argv[]) {

    if (SDL_Init(SDL_INIT_VIDEO) < 0) { 
        std::cerr << "SDL could not be initialised! Error caught: " << SDL_GetError() << std::endl;
        return -1;
    } // checking to see if the SDL2 library can be initialised for processing video graphics








    return 0;
}