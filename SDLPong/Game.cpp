#include "Game.h"
Game::Game() {}

Game::~Game()
{
	delete(ball);
	delete(p1_paddle);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

bool Game::init()
{
	//init sdl with desired functionality
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "SDL could not initialize!  SDL_Error: " << SDL_GetError() << std::endl;
		return false;
	}
	else
	{
		//create the window
		window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (window == NULL)
		{
			std::cout << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
			return false;
		}

		//create the renderer
		else
		{
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
			if (renderer == NULL)
			{
				std::cout << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
				return false;
			}

			//init renderer and png loading
			else
			{
				SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);

				//init png functionality
				if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
				{
					std::cout << "SDL_image could not be initialized! SDL_Image_Error: " << IMG_GetError() << std::endl;
					return false;
				}
			}
		}

		ball = new Ball(640 / 2, 480 / 2, "./resources/ball.png", renderer);
		ball->reset();
		
		p1_paddle = new Paddle(0, 0, "./resources/p1_paddle.png", renderer);
		p1_paddle->reset();

		return true;
	}
}

void Game::start()
{
	is_running = true;
	SDL_Event event;

	while (is_running)
	{
		Uint32 frame_time = SDL_GetTicks();

		while (SDL_PollEvent(&event) != 0)
		{
			if (event.type == SDL_QUIT)
			{
				is_running = false;
			}
		}

		handle_input();
		update();
		draw();

		cap_framerate(frame_time);
	}
}

void Game::handle_input()
{
	const Uint8* state = SDL_GetKeyboardState(NULL);
	p1_paddle->handle_input(state);

	if (state[SDL_SCANCODE_SPACE])
		ball->start(3);
}

void Game::update()
{
	ball->update();
	p1_paddle->update();
}

void Game::draw()
{
	//clear screen
	SDL_RenderClear(renderer);

	//drawing here
	ball->draw(renderer);
	p1_paddle->draw(renderer);
	//update screen
	SDL_RenderPresent(renderer);
}

void Game::cap_framerate(Uint32 frame_time)
{
	if ((1000 / FPS) > SDL_GetTicks() - frame_time)
	{
		SDL_Delay(1000 / FPS - (SDL_GetTicks() - frame_time));
	}
}

