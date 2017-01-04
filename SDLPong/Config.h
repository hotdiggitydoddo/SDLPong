#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <cmath>

#define _USE_MATH_DEFINES

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define FPS 60

#define PADDLE_OFFSET 50
#define MAX_BOUNCE_ANGLE 70

inline void logger(std::string msg)
{
	std::cout << msg.c_str() << std::endl;
}