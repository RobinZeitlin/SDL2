#include "Game.h"
#include "game/actors/Actor.h"
#include <string>

//SDL_Texture* playerTexture;


Game::Game()
{
	//init actorlist
	for (int i = 0; i < MAX_ACTORS; i++)
	{
		actorList[i] = nullptr;
	}

	lastTime = 0;
	deltaTime = 0.0f;
}

Game::~Game()
{	 
	
}

void Game::init(const char* title, int xPos, int yPos, int width, int height, bool fullscreen)
{
	Debug::startUp();

	int flags = 0;
	if (fullscreen)
	{
		Debug::log("Fullscreen Active...");
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		// window init
		window = SDL_CreateWindow(title, xPos, yPos, width, height, flags);
		if (window)
		{
			Debug::log("Window initialized");
		}

		// renderer init
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
		if (renderer)
		{
			Debug::log("Renderer initialized");
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		}

		isRunning = true;
	}
	else
	{
		isRunning = false;
	}

	textureManager = new TextureManager();
	textureManager->init(renderer);

	player = new Player();
	spawnActor(player, glm::vec3(100));

	camera = new Camera(100, 100, width, height);

	chunk = new Chunk();
	chunk->Init();
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

		// key press
		case SDL_KEYDOWN: 
			switch (event.key.keysym.sym)
			{
			case SDLK_ESCAPE:
				isRunning = false;
				break;
			}
			break;

		default:

			break;
	}
}

void Game::update()
{
	Uint32 currentTime = SDL_GetTicks();
	deltaTime = (currentTime - lastTime) / 1000.0f; // Convert to seconds
	lastTime = currentTime;

	for (int i = 0; i < MAX_ACTORS; i++)
	{
		if (actorList[i] != nullptr)
		{
			actorList[i]->update();
		}
	}

	if (player != nullptr)	{
		camera->updateCamera(actorList[0], deltaTime);
	}
}

void Game::render()
{
	SDL_RenderClear(renderer);

	chunk->RenderChunk(renderer, player, camera);

	for (int i = 0; i < MAX_ACTORS; i++)
	{
		if (actorList[i] != nullptr)
		{
			actorList[i]->render(renderer, camera);
		}
	}

	SDL_RenderPresent(renderer);

}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);

	Debug::warning("GAME CLOSED");
}

