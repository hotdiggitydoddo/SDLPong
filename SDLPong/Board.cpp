#include "Board.h"

Board::Board(SDL_Renderer* renderer)
{
	ball = new Ball(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, "./resources/ball.png", renderer, this);
	p1_paddle = new Paddle(0, 0, "./resources/p1_paddle.png", renderer);

	ball->reset();
	p1_paddle->reset();
}

Board::~Board()
{
	delete(ball);
	delete(p1_paddle);
}

void Board::handle_input(const Uint8* kb_state)
{
	p1_paddle->handle_input(kb_state);

	if (kb_state[SDL_SCANCODE_SPACE])
		ball->start(-8);
}

void Board::update()
{
	ball->update();
	p1_paddle->update();
	check_collision();
}

void Board::draw(SDL_Renderer* renderer)
{
	ball->draw(renderer);
	p1_paddle->draw(renderer);
}

void Board::check_collision()
{

}