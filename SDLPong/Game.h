#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "Ball.h"
#include "Paddle.h"

class Game
{
private:
	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;
	bool is_running = false;
	void cap_framerate(Uint32 frame_time);

	Ball* ball = NULL;
	Paddle* p1_paddle = NULL;

public:
	const int SCREEN_WIDTH = 640;
	const int SCREEN_HEIGHT = 480;
	const int FPS = 60;

	Game();
	~Game();
	bool init();
	void start();
	void handle_input();
	void update();
	void draw();
};

