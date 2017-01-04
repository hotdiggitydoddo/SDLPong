#pragma once

struct Intersection
{
	float cx, cy, time, nx, ny, ix, iy;
	Intersection(float x, float y, float _time, float _nx, float _ny, float _ix, float _iy)
	{
		cx = x;
		cy = y;
		time = _time;
		nx = _nx;
		ny = _ny;
		ix = _ix;
		iy = _iy;
	}
};
