#include "Game.h"

SDL_Texture* playerTexture;
SDL_Rect srcR, destR;

Game::Game() 
{

}

Game::~Game()
{

}

void Game::init(const char* title, int xPos, int yPos, int width, int height, bool fullscreen)
{
	debug = new Debug();
	debug->startUp();

	int flags = 0;
	if (fullscreen)
	{
		debug->log("Fullscreen Active...");
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		// window init
		window = SDL_CreateWindow(title, xPos, yPos, width, height, flags);
		if (window)
		{
			debug->log("Window initialized");
		}

		// renderer init
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
		if (renderer)
		{
			debug->log("Renderer initialized");
			SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
		}

		isRunning = true;
	}
	else
	{
		isRunning = false;
	}

	SDL_Surface* tempSurface = IMG_Load("assets/cube.png");
	playerTexture = SDL_CreateTextureFromSurface(renderer, tempSurface);
	SDL_FreeSurface(tempSurface);
}

void Game::handleEvents()
{
	SDL_Event event;

	SDL_PollEvent(&event);

	switch (event.type)
	{
		case SDL_QUIT:
			isRunning = false;
		break;

		default:
			break;
	}
}

void Game::update()
{
	destR.h = 32;
	destR.w = 32;
}

void Game::render()
{
	SDL_RenderClear(renderer);

	// pass things to render in here.

	SDL_RenderCopy(renderer, playerTexture, NULL, &destR);

	SDL_RenderPresent(renderer);

}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);

	debug->warning("GAME CLOSED");
}