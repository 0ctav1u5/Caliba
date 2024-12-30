#include <iostream>
#include <SDL.h>
#include <random>
#include "Paddle.hpp"
#include "Game.hpp"


void Paddle::SetColour(int R, int G, int B) { // sets members to params
	this->R = R, this->G = G, this->B = B;
}


void Paddle::RenderPaddle(SDL_Renderer* renderer) {
	SDL_SetRenderDrawColor(renderer, R, G, B, opaque); // sets the draw colour
	SDL_Rect filledRect = { posx, posy, width, height };
	SDL_RenderFillRect(renderer, &filledRect);
}

// pos x for a shape on the screen is the left most point of the object
// pos y is the top left corner of the object 

void Paddle::Move(int changex, int changey) {
	posx += changex; // - x moves left, + x moves right 
	// posy += changey; - y moves up, + y moves down
}

int Paddle::GetX() { 
	return this->posx;
}

int Paddle::GetY() {
	return this->posy;
}

int Paddle::GetWidth() {
	return this->width;
}

int Paddle::GetHeight() {
	return this->height;
}