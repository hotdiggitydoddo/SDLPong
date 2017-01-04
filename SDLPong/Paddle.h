#pragma once

#include "Config.h"
#include "Sprite.h"

class Paddle : public Sprite
{
private:
	int vel;

public:
	Paddle(int x, int y, std::string path, SDL_Renderer* renderer) : Sprite(x, y, path, renderer) {}
	void handle_input(const Uint8* kb_state);
	void update();
	void reset();
	int get_width();
	int get_height();
};