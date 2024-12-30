#include <iostream>
#include <SDL.h>
#ifndef PADDLE_HPP
#define PADDLE_HPP

class Paddle {
private:
	int HP = 100; // base HP of 100
	int R = 0, G = 0, B = 0;
	int opaque = 255; // 255 = fully opaque, closer to 0 = more transparent
	int posx, posy;
	int width, height;
public:

	Paddle(int StartX, int StartY, int StartWidth, int StartHeight) : // creates paddle shape
		posx(StartX), posy(StartY), width(StartWidth), height(StartHeight){} // with position


	void SetColour(int R, int G, int B);
	void RenderPaddle(SDL_Renderer* renderer);

	void Move(int changex, int changey);

	// util
	void SetHP(int hp);
	void DecreaseHP(int damage);
	int GetX();
	int GetY();
	int GetHP();
	int GetWidth();
	int GetHeight();

};

#endif