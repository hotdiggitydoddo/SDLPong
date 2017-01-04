#include "Ball.h"

Intersection* Ball::check_paddle_collision()
{
	int new_x = x + vel_x;
	int new_y = y + vel_y;

	Paddle* p1_paddle = board->p1_paddle;
	float float_max = std::numeric_limits<float>::max();

	float l = p1_paddle->x - (p1_paddle->get_width() / 2);
	float t = p1_paddle->y - (p1_paddle->get_height() / 2);
	float r = p1_paddle->x + (p1_paddle->get_width() / 2);
	float b = p1_paddle->y + (p1_paddle->get_height() / 2);

	// If the bounding box around the start and end points (+radius on all
	// sides) does not intersect with the rectangle, definitely not an
	// intersection
	if ((std::max(x, new_x) + origin_x < l) ||
		(std::min(x, new_x) - origin_x > r) ||
		(std::max(y, new_y) + origin_x < t) ||
		(std::min(y, new_y) - origin_x > b))
	{
		return NULL;
	}

	float d_x = new_x - x;
	float d_y = new_y - y;
	float inv_d_x = (d_x == 0.0f ? 0.0f : 1.0f / d_x);
	float inv_d_y = (d_y == 0.0f ? 0.0f : 1.0f / d_y);
	float corner_x = float_max;
	float corner_y = float_max;

	// Calculate intersection times with each side's plane
	// Check each side's quadrant for single-side intersection
	// Calculate Corner

	/** Left Side **/
	// Does the circle go from the left side to the right side of the rectangle's left?
	if (x - origin_x < l && new_x + origin_x > l)
	{
		float l_time = ((l -origin_x) - x) * inv_d_x;
		if (l_time >= 0.0f && l_time <= 1.0f)
		{
			float ly = d_y * l_time + y;
			// Does the collisions point lie on the left side?
			if (ly >= t && ly <= b)
			{
				return new Intersection(d_x * l_time + x, ly, l_time, -1, 0, l, ly);
			}
		}
		corner_x = l;
	}

	/** Right Side **/
	// Does the circle go from the right side to the left side of the rectangle's right?
	if (x + origin_x > r && new_x - origin_x < r)
	{
		float rtime = (x - (r + origin_x)) * -inv_d_x;
		if (rtime >= 0.0f && rtime <= 1.0f)
		{
			float ry = d_y * rtime + y;
			// Does the collisions point lie on the right side?
			if (ry >= t && ry <= b)
			{
				return new Intersection(d_x * rtime + x, ry, rtime, 1, 0, r, ry);
			}
		}
		corner_x = r;
	}

	/** Top Side **/
	// Does the circle go from the top side to the bottom side of the rectangle's top?
	if (y - origin_x < t && new_y + origin_x > t)
	{
		float ttime = ((t - origin_x) - y) * inv_d_y;
		if (ttime >= 0.0f && ttime <= 1.0f)
		{
			float tx = d_x * ttime + x;
			// Does the collisions point lie on the top side?
			if (tx >= l && tx <= r)
			{
				return new Intersection(tx, d_y * ttime + y, ttime, 0, -1, tx, t);
			}
		}
		corner_y = t;
	}

	/** Bottom Side **/
	// Does the circle go from the bottom side to the top side of the rectangle's bottom?
	if (y + origin_x > b && new_y - origin_x < b)
	{
		float btime = (y - (b + origin_x)) * -inv_d_y;
		if (btime >= 0.0f && btime <= 1.0f) {
			float bx = d_x * btime + x;
			// Does the collisions point lie on the bottom side?
			if (bx >= l && bx <= r)
			{
				return new Intersection(bx, d_y * btime + y, btime, 0, 1, bx, b);
			}
		}
		corner_y = b;
	}

	// No intersection at all!
	if (corner_x == float_max && corner_y == float_max)
	{
		return NULL;
	}

	// Account for the times where we don't pass over a side but we do hit it's corner
	if (corner_x != float_max && corner_y == float_max)
	{
		corner_y = (d_y > 0.0f ? b : t);
	}
	if (corner_y != float_max && corner_x == float_max)
	{
		corner_x = (d_x > 0.0f ? r : l);
	}

	/* Solve the triangle between the start, corner, and intersection point.
	*
	*           +-----------T-----------+
	*           |                       |
	*          L|                       |R
	*           |                       |
	*           C-----------B-----------+
	*          / \
	*         /   \r     _.-E
	*        /     \ _.-'
	*       /    _.-I
	*      / _.-'
	*     S-'
	*
	* S = start of circle's path
	* E = end of circle's path
	* LTRB = sides of the rectangle
	* I = {ix, iY} = point at which the circle intersects with the rectangle
	* C = corner of intersection (and collision point)
	* C=>I (r) = {nx, ny} = radius and intersection normal
	* S=>C = cornerdist
	* S=>I = intersectionDistance
	* S=>E = lineLength
	* <S = innerAngle
	* <I = angle1
	* <C = angle2
	*/

	double inverseRadius = 1.0 / origin_x;
	double lineLength = sqrt(d_x * d_x + d_y * d_y);
	double corner_dx = corner_x - x;
	double corner_dy = corner_y - y;
	double cornerDistance = sqrt(corner_dx * corner_dx + corner_dy * corner_dy);
	double innerAngle = acos((corner_dx * d_x + corner_dy * d_y) / (lineLength * cornerDistance));

	// If the circle is too close, no intersection.
	if (cornerDistance < origin_x)
	{
		return NULL;
	}

	// If inner angle is zero, it's going to hit the corner straight on.
	if (innerAngle == 0.0f)
	{
		float time = (float)((cornerDistance - origin_x) / lineLength);

		// If time is outside the boundaries, return null. This algorithm can
		// return a negative time which indicates a previous intersection, and
		// can also return a time > 1.0f which can predict a corner intersection.
		if (time > 1.0f || time < 0.0f)
		{
			return NULL;
		}

		float ix = time * d_x + x;
		float iy = time * d_y + y;
		float nx = (float)(corner_dx / cornerDistance);
		float ny = (float)(corner_dy / cornerDistance);

		return new Intersection(ix, iy, time, nx, ny, corner_x, corner_y);
	}

	double innerAngleSin = sin(innerAngle);
	double angle1Sin = innerAngleSin * cornerDistance * inverseRadius;

	// The angle is too large, there cannot be an intersection
	if (abs(angle1Sin) > 1.0f)
	{
		return NULL;
	}

	double angle1 = M_PI - asin(angle1Sin);
	double angle2 = M_PI - innerAngle - angle1;
	double intersectionDistance = origin_x * sin(angle2) / innerAngleSin;

	// Solve for time
	float time = (float)(intersectionDistance / lineLength);

	// If time is outside the boundaries, return null. This algorithm can
	// return a negative time which indicates a previous intersection, and
	// can also return a time > 1.0f which can predict a corner intersection.
	if (time > 1.0f || time < 0.0f)
	{
		return NULL;
	}

	// Solve the intersection and normal
	float ix = time * d_x + x;
	float iy = time * d_y + y;
	float nx = (float)((ix - corner_x) * inverseRadius);
	float ny = (float)((iy - corner_y) * inverseRadius);

	return new Intersection(ix, iy, time, nx, ny, corner_x, corner_y);
}

void Ball::update()
{
	if (vel_x == 0 && vel_y == 0)
		return;

	//check top/bottom collision
	if ((y + origin_y + vel_y >= SCREEN_HEIGHT) || y - origin_y <= 0)
	{
		vel_y *= -1;
		y += vel_y;
		return;
	}
	
	if (x + origin_x * 2 >= SCREEN_WIDTH)
	{
		vel_x *= -1;
		x += vel_x;
		return;
	}

	int new_x = x + vel_x;
	int new_y = y + vel_y;

	Intersection* intersection = check_paddle_collision();

	if (intersection != NULL)
	{
		std::cout << "Intersection: cx: " << intersection->cx << " cy: " << intersection->cy << " time: " << intersection->time << " nx: " << intersection->nx << " ny: " << intersection->ny << " ix: " << intersection->ix << " iy: " << intersection->iy << std::endl;
		// Project Future Position
		float remainingTime = 1.0f - intersection->time;
		float dx = new_x - x;
		float dy = new_y - y;
		float dot = dx * intersection->nx + dy * intersection->ny;
		float ndx = dx - 2 * dot * intersection->nx;
		float ndy = dy - 2 * dot * intersection->ny;
		float newx = intersection->cx + ndx * remainingTime;
		float newy = intersection->cy + ndy * remainingTime;
		x = newx;
		y = newy;

		vel_x = ndx;
		vel_y = ndy;
	}
	else
	{
		x = new_x;
		y = new_y;
	}
	
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
