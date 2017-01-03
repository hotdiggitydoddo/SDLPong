#pragma once

#include "Config.h"
#include "Board.h"

class Game
{
private:
	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;
	Board* board;
	bool is_running = false;
	
	void handle_input();
	void update();
	void draw();
	void cap_framerate(Uint32 frame_time);

public:
	~Game();
	bool init();
	void start();
};

