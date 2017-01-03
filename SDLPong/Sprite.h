#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

class Sprite
{
private:
	SDL_Texture *texture = NULL;
	SDL_Rect rect;

	

protected:
	int width, height, origin_x, origin_y;

public:
	Sprite(std::string path, SDL_Renderer *renderer);
	Sprite(int x, int y, std::string path, SDL_Renderer *renderer);
	~Sprite();
	virtual void update();
	void draw(SDL_Renderer *renderer);
	int x, y;
};

