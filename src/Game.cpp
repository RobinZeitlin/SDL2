#include <string>

#include "Game.h"

#include "engine/AABB.h"

#include "game/actors/Actor.h"
#include "game/terrain/LoadLevel.h"

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

	loadLevel = new LoadLevel();
	loadLevel->load_level_file("src/level");
}

void Game::spawnPlayer(glm::vec2 position) {
	if (player == nullptr) {
		player = new Player();
		spawnActor(player, position);
	}

	camera = new Camera(position.x, position.y, 800, 600);
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
	deltaTime = (currentTime - lastTime) / 1000.0f;
	lastTime = currentTime;

	for (int i = 0; i < MAX_ACTORS; i++)
	{
		if (actorList[i] != nullptr)
		{
			if (actorList[i]->isDestroyed) {
				auto renderLayer = actorList[i]->render_layer;
				auto layerIndex = static_cast<size_t>(renderLayer);

				layers[layerIndex].erase(std::remove(layers[layerIndex].begin(), layers[layerIndex].end(), actorList[i]), layers[layerIndex].end());

				actorList[i] = nullptr;

				return;
			}

			actorList[i]->update(deltaTime);

			if (actorList[i]->actorName == "Player")
			{
				camera->updateCamera(actorList[i], deltaTime);
			}
		}
	}
}

void Game::render()
{
	SDL_RenderClear(renderer);

	for (size_t layer = 0; layer < layers.size(); layer++) {
		for (auto* actor : layers[layer]) {
			if (actor != nullptr) {
				actor->render(renderer, camera);
			}
		}
	}

	for (size_t i = 0; i < particleControllers.size(); ) {
		auto* particleCtrl = particleControllers[i];

		if (particleCtrl->isEmpty()) {
			particleControllers.erase(particleControllers.begin() + i);
			return;
		}

		particleCtrl->render(renderer);
		++i;
	}

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderPresent(renderer);
}

Actor* Game::get_overlapping_actor(Actor* other, Collision_Channel channel)
{
	for (int i = 0; i < MAX_ACTORS; i++){
		if (actorList[i] == other || actorList[i] == nullptr || actorList[i]->collision_channel != channel)
			continue;

		AABB a = AABB::from_position_size(other->transform);
		AABB b = AABB::from_position_size(actorList[i]->transform);

		if (aabb_overlap(a, b)){
			return actorList[i];
		}
	}

	return nullptr;
}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);

	Debug::warning("GAME CLOSED");
}

