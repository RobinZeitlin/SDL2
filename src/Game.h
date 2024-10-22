#pragma once

#ifndef Game_h
#define Game_h

#include <stdio.h>

#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>
#include <glm.hpp>
#include <array>

#include "game/actors/Actor.h"
#include "game/actors/Player.h"
#include "game/actors/Boomerang.h"
#include "Camera.h"

#include "engine/Debug.h"
#include "engine/TextureManager.h"
#include "engine/ParticleController.h"

#define MAX_ACTORS 1000

#define GIZMO_COLOR { 0, 255, 0, 255 }

class LoadLevel;

class Game
{
public:
	Game();

	~Game();

	void init(const char* title, int xPos, int yPos, int width, int height, bool fullscreen);

	void spawnPlayer(glm::vec2 position);

	void handleEvents();
	void update();
	void render();
	void clean();

	template <typename Actor>
	void spawnActor(Actor* actor, const glm::vec2& position, const glm::vec2& rotation = glm::vec2(0.0f, 0.0f), const glm::vec2& scale = glm::vec2(32.0f, 32.0f))
	{
		for (int i = 0; i < MAX_ACTORS; ++i)
		{
			if (actorList[i] == nullptr)
			{
				actorList[i] = actor;
				actorList[i]->transform.position = position;
				actorList[i]->transform.rotation = rotation;
				actorList[i]->transform.scale = scale;

				break;
			}
		}
	}

	Actor* get_overlapping_actor(Actor* other, Collision_Channel channel);
	bool running()
	{
		return isRunning;
	}

	Actor* actorList[MAX_ACTORS];
	std::array<std::vector<Actor*>, static_cast<size_t>(Render_Layer::LayerCount)> layers;
	std::vector<ParticleController*> particleControllers;

	Camera* camera;
	Player* player;
	LoadLevel* loadLevel;
	SDL_Window* window;
	SDL_Renderer* renderer;

	float deltaTime;

private:
	bool isRunning;
	float lastTime;
};

extern Game* game;

#endif // game_h


