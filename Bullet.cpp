#include <iostream>
#include <SDL.h>
#include <random>
#include "Game.hpp"
#include "Bullet.hpp"

void Bullet::SetColour(int R, int G, int B) { // sets members to params
	this->R = R, this->G = G, this->B = B;
}

void Bullet::RenderBullet(SDL_Renderer* renderer) {
	SDL_SetRenderDrawColor(renderer, R, G, B, opaque); // sets the draw colour
	SDL_Rect filledRect = { posx, posy, width, height };
	SDL_RenderFillRect(renderer, &filledRect);
}

// pos x for a shape on the screen is the left most point of the object
// pos y is the top left corner of the object 

void Bullet::Move(int changex, int changey) {
	posx += changex; // This will move the bullet horizontally (though we're not using it here)
	posy += changey; // This should correctly move the bullet upwards when changey is negative
}

int Bullet::GetX() {
	return this->posx;
}

int Bullet::GetY() {
	return this->posy;
}

int Bullet::GetWidth() {
	return this->width;
}