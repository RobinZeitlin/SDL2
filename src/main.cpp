#include "Game.h"

Game* game = nullptr;

int main(int args, char *argv[])
{
	game = new Game();

	const char* title = "SDL2";

	game->init(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1000, 800, false);

	while (game->running()) 
	{
		game->handleEvents();
		game->update();
		game->render();
	}

	game->clean();

	return 0;
}