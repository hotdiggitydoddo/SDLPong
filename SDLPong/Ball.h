#pragma once

#include <limits>
#include <algorithm>

#include "Config.h"
#include "Sprite.h"
#include "Board.h"
#include "intersection.h"

class Board;

class Ball : public Sprite
{
private:
	int vel_x, vel_y;
	Board* board;

public:
	Ball(int x, int y, std::string path, SDL_Renderer* renderer, Board* board) : Sprite(x, y, path, renderer) 
	{
		this->board = board;
	}
	void update();
	void reset();
	void start(int vel);
	Intersection* check_paddle_collision();
};
