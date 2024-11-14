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

	if (bEditor)
		Debug::log("In Editor Mode");
	else
		Debug::log("Not In Editor Mode");

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;

	ImGui_ImplSDL2_InitForSDLRenderer(window, renderer);
	ImGui_ImplSDLRenderer2_Init(renderer);

	textureManager = new TextureManager();
	textureManager->init(renderer);

	loadLevel = new LoadLevel();
	loadLevel->load_level_file("src/levels/level", true);

	pathFindingManager = new PathFindingManager(50, 50);

	if(bEditor)
		levelEditor = new LevelEditor(renderer, camera);
}

void Game::spawnPlayer(glm::vec2 position) {

	if (!bEditor)
	{
		if (player == nullptr) {
			player = new Player();
			spawnActor(player, position);
		}
	}

	camera = new Camera(position.x, position.y, 800, 600);
}

void Game::spawn_particle_system(ParticleController* particleCtrl)
{
	if (particleControllers.size() >= 20) return;

	particleControllers.push_back(particleCtrl);
}

void Game::handleEvents()
{
	SDL_Event event;

	SDL_PollEvent(&event);

	ImGui_ImplSDL2_ProcessEvent(&event);

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

	if (bEditor)
		levelEditor->update(deltaTime);
}

void Game::render()
{
	static float lastTime = 0.0f;
	static float deltaTime = 0.0f;
	float currentTime = SDL_GetTicks() / 1000.0f;
	deltaTime = currentTime - lastTime;
	lastTime = currentTime;

	float fps = 1.0f / deltaTime;

	SDL_RenderClear(renderer);

	for (size_t layer = 0; layer < layers.size(); layer++) {
		for (auto* actor : layers[layer]) {
			if (actor != nullptr) {
				actor->render(renderer, camera);
			}
		}
	}

	for (size_t i = 0; i < particleControllers.size(); i++) {
		auto* particleCtrl = particleControllers[i];

		if (particleCtrl->is_empty()) {
			particleControllers.erase(particleControllers.begin() + i);
			delete particleCtrl;
			continue;
		}
		else
		particleCtrl->render(renderer);
	}

	ImGui_ImplSDLRenderer2_NewFrame();
	ImGui_ImplSDL2_NewFrame();
	ImGui::NewFrame();

	if(bEditor)
	levelEditor->render(renderer);

	ImGui::SetNextWindowPos(ImVec2(10, 10), ImGuiCond_Always);
	ImGui::SetNextWindowBgAlpha(0);
	ImGui::Begin("FPS Display", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoScrollbar);
	ImGui::Text("FPS: %.1f", fps);
	ImGui::End();

	ImGui::Render();

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

	ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData(), renderer);

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
	ImGui_ImplSDLRenderer2_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();

	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);

	Debug::warning("GAME CLOSED");
}

