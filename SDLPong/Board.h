#pragma once

#include "Config.h"
#include "Ball.h"
#include "Paddle.h"

class Board
{
public:
	Board(SDL_Renderer* renderer);
	Board() {}
	~Board();
	void handle_input(const Uint8* kb_state);
	void update();
	void draw(SDL_Renderer* renderer);

private:
	Ball* ball;
	Paddle* p1_paddle;
	//SDL_Renderer* renderer;
};

