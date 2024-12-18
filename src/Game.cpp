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
	spline = new Spline();
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

	camera = new Camera(0, 0, 1000, 800);

	loadLevel = new LoadLevel();
	loadLevel->load_level_file("src/levels/level", true);

	pathFindingManager = new PathFindingManager(50, 50);

	if(bEditor)
		levelEditor = new LevelEditor(renderer, camera);
}

void Game::spawnPlayer(glm::vec2 spawnPos) {
	if (!bEditor) {
		player = new Player(spawnPos);
		spawnActor(player, spawnPos);
	}
}

void Game::spawn_particle_system(std::unique_ptr<ParticleController> particleCtrl)
{
	if (particleControllers.size() >= 20) return;

	particleControllers.push_back(std::move(particleCtrl));
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

	for (int i = 0; i < MAX_ACTORS; i++) {
		if (actorList[i] != nullptr) {
			if (actorList[i]->isDestroyed) {
				auto renderLayer = actorList[i]->render_layer;
				auto layerIndex = static_cast<size_t>(renderLayer);

				layers[layerIndex].erase(std::remove(layers[layerIndex].begin(), layers[layerIndex].end(), actorList[i]), layers[layerIndex].end());
				actorList[i] = nullptr;

				continue;
			}

			actorList[i]->update(deltaTime);
		}
	}

	if (bEditor && levelEditor != nullptr) {
		levelEditor->update(deltaTime);
	}
	else if (bEditor && levelEditor == nullptr) {
		levelEditor = new LevelEditor(renderer, camera);
	}
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
		ParticleController* particleCtrl = particleControllers[i].get();

		if (particleCtrl->is_empty()) {
			particleControllers.erase(particleControllers.begin() + i);
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

	spline->render_debug(renderer);

	ImGui::SetNextWindowPos(ImVec2(30, 10), ImGuiCond_Always);
	ImGui::SetNextWindowBgAlpha(0);
	ImGui::Begin("FPS Display", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoScrollbar);
	ImGui::Text("FPS: %.1f", fps);
	ImGui::End();

	ImGui::SetNextWindowBgAlpha(0);
	ImGui::Begin("Play Button", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoScrollbar);
	ImTextureID icon = bEditor ? (ImTextureID)textureManager->getTexture("pauseicon") : (ImTextureID)textureManager->getTexture("playicon");
	if (ImGui::ImageButton("Play", icon, { 30, 30 }))
	{
		std::cout << "Play Level!" << std::endl;
		switch_play_mode(!bEditor);
	}
	ImGui::End();

	ImGui::Render();

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

	ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData(), renderer);

	SDL_RenderPresent(renderer);
}

Actor* Game::get_overlapping_actor(Actor* other, Collision_Channel channel)
{
	for (int i = 0; i < MAX_ACTORS; i++) {
		if (actorList[i] == other || actorList[i] == nullptr || actorList[i]->collision_channel != channel)
			continue;

		AABB a = AABB::from_position_size(other->transform);
		AABB b = AABB::from_position_size(actorList[i]->transform);

		if (aabb_overlap(a, b)) {
			return actorList[i];
		}
	}

	return nullptr;
}

void Game::switch_play_mode(bool inEditorMode)
{
	bEditor = inEditorMode;

	if (bEditor) {
		loadLevel->load_level_file(loadLevel->lastLevelWithPath, true);

		if (player != nullptr)
		{
			player->weapon->destroy();
			player->destroy();
			player = nullptr;
		}
	}
	else {
		loadLevel->save_level(loadLevel->lastLevelWithPath);
		loadLevel->load_level_file(loadLevel->lastLevelWithPath, true);
		levelEditor->cameraController->destroy();
	}
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

