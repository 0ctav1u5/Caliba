#include <iostream>
#include <SDL.h>
#include <cmath> // for circle drawing logic
#ifndef BALL_HPP
#define BALL_HPP


class Ball {
private:
	int R = 0, G = 0, B = 0;
	int opaque = 255; // 255 = fully opaque, closer to 0 = more transparent
	float posx, posy;
	int width;
public:
	Ball(float StartX, float StartY, int StartWidth) : // creates paddle shape
		posx(StartX), posy(StartY), width(StartWidth) {} // with position

	void SetColour(int R, int G, int B);
	void RenderBall(SDL_Renderer* renderer);

	void Move(float changex, float changey);

	int GetX();
	int GetY();
	int GetWidth();
};







#endif