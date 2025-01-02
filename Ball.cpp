#include <iostream>
#include <SDL.h>
#include <cmath> // for circle drawing logic
#include "Ball.hpp"

void Ball::RenderBall(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, R, G, B, opaque);

    int radius = width / 2; 
    int centreX = posx; 
    int centreY = posy;

    int x = radius;
    int y = 0;
    int decisionmaker = 1 - x; // Decision parameter

    while (x >= y) {
        // PosX = 250, PosY = 250, Width = 20, radius = 10, centre point (250, 250)
        // far right point (260, 250), far left point (240, 250)
        // X: 250 - 10 = 240, Y: 250 + 0 = 250; X: 250 + 10 = 260, Y: 250 + 0 = 250 
        // first point: {240, 250} second point: {260, 250}
        // this creates a horizontal line from the far left point to a far left point
        SDL_RenderDrawLine(renderer, centreX - x, centreY + y, centreX + x, centreY + y);


        // 250 - 0, 250 + 10 = {250, 260}; 250 + 0, 250 + 10 = {250, 260}
        // no line drawn in the first iteration, changes when y is incremented
        SDL_RenderDrawLine(renderer, centreX - y, centreY + x, centreX + y, centreY + x);

        // 250 - 10, 250 - 0 = {240, 250}; 250 + 10, 250 - 0 = {260, 250}
        // another horizontal line going from the far left point to the far right point
        SDL_RenderDrawLine(renderer, centreX - x, centreY - y, centreX + x, centreY - y);

        // 250 - 0, 250 - 10 = {250, 240}; 250 + 0, 250 - 10 = {250, 240}
        // no line is drawn during the first iteration
        // In subsequent iterations, the line moves downward, forming the bottom half of the circle.
        SDL_RenderDrawLine(renderer, centreX - y, centreY - x, centreX + y, centreY - x);

        // 4 lines in total

        y++; // y gets incremented if either rule is true
        if (decisionmaker <= 0) { // this part here tells the program if more points need plotting
            decisionmaker += 2 * y + 1;
        }
        else {
            x--;
            decisionmaker += 2 * (y - x) + 1;
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
