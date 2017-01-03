#include "Ball.h"

void Ball::update()
{
	if (this->vel_x == 0 && this->vel_y == 0)
		return;

	int x = get_x();
	int y = get_y();
	if ((x + origin_x + vel_x >= 640) || x - origin_x <= 0)
		vel_x *= -1;
	if ((y + origin_y + vel_y >= 480) || y - origin_y <= 0)
		vel_y *= -1;

	set_x(x += vel_x);
	set_y(y += vel_y);
}

void Ball::reset()
{
	this->set_x(640 / 2);
	this->set_y(480 / 2);
	vel_x = 0;
	vel_y = 0;
}

void Ball::start(int vel)
{
	vel_x = vel;
	vel_y = vel;
}
