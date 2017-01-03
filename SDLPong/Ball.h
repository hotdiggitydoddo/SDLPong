#pragma once

#include "Config.h"
#include "Sprite.h"

class Ball : public Sprite
{
private:
	int vel_x, vel_y;

public:
	Ball(int x, int y, std::string path, SDL_Renderer* renderer) : Sprite(x, y, path, renderer) {}
	void update();
	void reset();
	void start(int vel);
};
