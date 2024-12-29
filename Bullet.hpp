#include <iostream>
#include <SDL.h>

#ifndef BULLET_HPP
#define BULLET_HPP


class Bullet {
private:
	int R = 0, G = 0, B = 0;
	int opaque = 255; 
	int posx, posy;
	int width, height;
public:

	Bullet(int StartX, int StartY, int StartWidth, int StartHeight) : // creates paddle shape
		posx(StartX), posy(StartY), width(StartWidth), height(StartHeight) {} // with position

	void SetColour(int R, int G, int B);
	void RenderBullet(SDL_Renderer* renderer);

	void Move(int changex, int changey);

	// util
	int GetX();
	int GetY();
	int GetWidth();
};

#endif