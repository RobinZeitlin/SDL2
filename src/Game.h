#pragma once

#ifndef Game_h
#define Game_h

#include <stdio.h>

#include "SDL.h"
#include "SDL_image.h"
#include "glm.hpp"

#include "game/actors/Actor.h"
#include "game/actors/Player.h"
#include "game/terrain/Chunk.h"

#include "engine/Debug.h"
#include "engine/TextureManager.h"

#define MAX_ACTORS 100

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
	void spawnActor(Actor* actor, const glm::vec3& position, const glm::vec3& scale = glm::vec3(32.0f, 32.0f, 1.0f))
	{
		for (int i = 0; i < MAX_ACTORS; ++i)
		{
			if (actorList[i] == nullptr)
			{
				Actor* new_entity = new Actor();
				actorList[i] = new_entity;
			}
		}
	}

	bool running()
	{
		return isRunning;
	}

	Actor* actorList[MAX_ACTORS];
	Player* player;
	Chunk* chunk;

private:
	bool isRunning;

	SDL_Window* window;
	SDL_Renderer* renderer;
};
#endif // game_h
