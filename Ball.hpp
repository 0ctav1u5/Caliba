#include <iostream>
#include <SDL.h>
#include <cmath> // for circle drawing logic
#ifndef BALL_HPP
#define BALL_HPP


class Ball {
private:
	int R = 0, G = 0, B = 0;
	int opaque = 255; // 255 = fully opaque, closer to 0 = more transparent
	int posx, posy;
	int width, height;

public:
	Ball(int StartX, int StartY, int StartWidth, int StartHeight) : // creates paddle shape
		posx(StartX), posy(StartY), width(StartWidth), height(StartHeight) {} // with position

	void SetColour(int R, int G, int B);
	void RenderBall(SDL_Renderer* renderer);

	void Move(int changex, int changey);

	int GetX();
	int GetY();
	int GetWidth();
	int GetHeight();

};







#endif