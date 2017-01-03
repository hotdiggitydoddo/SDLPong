#include "Sprite.h"

Sprite::Sprite(std::string path, SDL_Renderer *renderer)
{
	SDL_Surface *loaded_surface = IMG_Load(path.c_str());
	if (loaded_surface == NULL)
	{
		std::cout << "Unable to load sprite texture from: " << path.c_str() << ". (SDL_image Error: " << IMG_GetError() << ")" << std::endl;
	}
	else
	{
		texture = SDL_CreateTextureFromSurface(renderer, loaded_surface);
		SDL_FreeSurface(loaded_surface);

		if (texture == NULL)
		{
			std::cout << "Unable to create sprite texture from: " << path.c_str() << ". (SDL_image Error: " << IMG_GetError() << ")" << std::endl;
		}
		else
		{
			SDL_QueryTexture(texture, NULL, NULL, &width, &height);
			origin_x = width / 2;
			origin_y = height / 2;
		}
	}
}

Sprite::Sprite(int x, int y, std::string path, SDL_Renderer* renderer) : Sprite(path, renderer)
{
	this->x = x;
	this->y = y;
}

Sprite::~Sprite()
{
	SDL_DestroyTexture(texture);
	texture = NULL;
}

void Sprite::update() {}

void Sprite::draw(SDL_Renderer *renderer)
{
	rect = { x - origin_x, y - origin_y, width, height };

	SDL_RenderCopy(renderer, texture, NULL, &rect);
}
