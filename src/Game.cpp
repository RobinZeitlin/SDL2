#include <string>

#include "Game.h"

#include "engine/AABB.h"

#include "game/actors/Actor.h"
#include "game/terrain/Chunk.h"

Game::Game()
{
	//init actorlist
	for (int i = 0; i < MAX_ACTORS; i++)
	{
		actorList[i] = nullptr;
	}

	lastTime = 0;
	deltaTime = 0.0f;

	player = nullptr;
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

	if (player == nullptr)
	{
		player = new Player();
		spawnActor(player, glm::vec2(100));
	}

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

	for (int i = 0; i < MAX_ACTORS; i++)
	{
		if (actorList[i] != nullptr)
		{
			actorList[i]->render(renderer, camera);
		}
	}

	SDL_RenderPresent(renderer);

}

Actor* Game::get_overlapping_actor(Actor* other, Collision_Channel channel)
{
	for (int i = 0; i < MAX_ACTORS; i++)
	{
		if (actorList[i] == other || actorList[i] == nullptr || actorList[i]->collision_channel != channel)
			continue;

		AABB a = AABB::from_position_size(other->transform);
		AABB b = AABB::from_position_size(actorList[i]->transform);

		if (aabb_overlap(a, b)) {
			std::cout << "coliding with : " << actorList[i]->transform.position.x << actorList[i]->transform.position.y << std::endl;
			return actorList[i];
		}
	}
}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);

	Debug::warning("GAME CLOSED");
}

