#include "Ball.h"

void Ball::update()
{
	if (vel_x == 0 && vel_y == 0)
		return;

	//keep ball within screen bounds for now
	if ((x + origin_x + vel_x >= SCREEN_WIDTH) || x - origin_x <= 0)
		vel_x *= -1;
	if ((y + origin_y + vel_y >= SCREEN_HEIGHT) || y - origin_y <= 0)
		vel_y *= -1;

	x += vel_x;
	y += vel_y;
}

void Ball::reset()
{
	x = SCREEN_WIDTH / 2;
	y = SCREEN_HEIGHT / 2;
	vel_x = 0;
	vel_y = 0;
}

void Ball::start(int vel)
{
	vel_x = vel;
	vel_y = vel;
}
