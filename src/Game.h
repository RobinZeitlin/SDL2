#pragma once

#ifndef Game_h
#define Game_h

#include <stdio.h>

#include "SDL.h"
#include "SDL_image.h"
#include "glm.hpp"

#include "game/actors/Actor.h"
#include "game/actors/Player.h"
#include "Camera.h"

#include "engine/Debug.h"
#include "engine/TextureManager.h"

#define MAX_ACTORS 100

class Chunk;

class Game
{
public:
	Game();

	~Game();

	void init(const char* title, int xPos, int yPos, int width, int height, bool fullscreen);

	void handleEvents();
	void update();
	void render();
	void clean();

	template <typename Actor>
	void spawnActor(Actor* actor, const glm::vec2& position, const glm::vec2& scale = glm::vec2(32.0f, 32.0f))
	{
		for (int i = 0; i < MAX_ACTORS; ++i)
		{
			if (actorList[i] == nullptr)
			{
				Actor* new_entity = new Actor();
				actorList[i] = new_entity;
				actorList[i]->transform.position = position;
				actorList[i]->transform.scale = { 32, 32 };
				std::cout << "Actor spawned with texture : " << actorList[i]->texture << std::endl;

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
	Camera* camera;
	Player* player;
	Chunk* chunk;

private:
	bool isRunning;

	SDL_Window* window;
	SDL_Renderer* renderer;

	float lastTime;
	float deltaTime;
};

extern Game* game;

#endif // game_h


