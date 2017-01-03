#include "Game.h"

int main(int argc, char** argv)
{
	Game pongGame;

	if (!pongGame.init())
		return -1;

	pongGame.start();

	return 0;

}