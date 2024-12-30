#include <iostream>
#include <SDL.h>
#include <cmath> // for circle drawing logic
#include "Ball.hpp"

void Ball::RenderBall(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, R, G, B, opaque);

    int radius = width / 2; // Assuming the ball is circular
    int centerX = posx;
    int centerY = posy;

    int x = radius;
    int y = 0;
    int decisionOver2 = 1 - x; // Decision parameter

    while (x >= y) {
        // Draw horizontal lines to fill the circle
        SDL_RenderDrawLine(renderer, centerX - x, centerY + y, centerX + x, centerY + y);
        SDL_RenderDrawLine(renderer, centerX - y, centerY + x, centerX + y, centerY + x);
        SDL_RenderDrawLine(renderer, centerX - x, centerY - y, centerX + x, centerY - y);
        SDL_RenderDrawLine(renderer, centerX - y, centerY - x, centerX + y, centerY - x);

        y++;
        if (decisionOver2 <= 0) {
            decisionOver2 += 2 * y + 1;
        }
        else {
            x--;
            decisionOver2 += 2 * (y - x) + 1;
        }
    }
}

void Ball::SetColour(int R, int G, int B) { 
	this->R = R, this->G = G, this->B = B;
}

void Ball::Move(int changex, int changey) {
	posx += changex; 
    posy += changey;
}

int Ball::GetX() {
	return this->posx;
}

int Ball::GetY() {
	return this->posy;
}

int Ball::GetWidth() {
	return this->width;
}

int Ball::GetHeight() {
	return this->height;
}