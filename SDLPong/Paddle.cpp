#include "Paddle.h"

void Paddle::handle_input(const Uint8* kb_state)
{
	if (kb_state[SDL_SCANCODE_UP])
		vel = -8;
	else if (kb_state[SDL_SCANCODE_DOWN])
		vel = 8;
	else
		vel = 0;
}

void Paddle::update()
{
	y += vel;

	if (y - origin_y < 0)
	{
		y = origin_y;
		vel = 0;
	}
	else if (y + origin_y > 480)
	{
		y = 480 - origin_y;
		vel = 0;
	}
}

void Paddle::reset()
{
	x = 50;
	y = 480 / 2;
	vel = 0;
}
