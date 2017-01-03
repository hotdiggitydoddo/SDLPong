#include "Ball.h"

void Ball::update()
{
	if (vel_x == 0 && vel_y == 0)
		return;

	//keep ball within screen bounds for now
	if ((x + origin_x + vel_x >= 640) || x - origin_x <= 0)
		vel_x *= -1;
	if ((y + origin_y + vel_y >= 480) || y - origin_y <= 0)
		vel_y *= -1;

	x += vel_x;
	y += vel_y;
}

void Ball::reset()
{
	x = 640 / 2;
	y = 480 / 2;
	vel_x = 0;
	vel_y = 0;
}

void Ball::start(int vel)
{
	vel_x = vel;
	vel_y = vel;
}
