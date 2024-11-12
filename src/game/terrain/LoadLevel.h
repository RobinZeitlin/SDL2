#pragma once

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "../../engine/Debug.h"
#include "../../Game.h"

#include "../terrain/Block.h"
#include "../terrain/GrassBlock.h"
#include "../terrain/Stairs.h"
#include "../actors/Enemy.h"

using namespace std;

class LoadLevel
{
public:
	void add_actor(Actor* actor) { currentLevel.push_back(actor); }

	void save_level(const std::string& saveFile);
	void clear_current_level();

	void fill_tool(glm::vec2 atPos);

	void place_actor(glm::vec2 atPos, Actor* actor);
	void add_actor(glm::vec2 gridPos, Actor* actor);
	void destroy_actor(glm::vec2 atPos);

	void spawn_level(const std::vector<std::string>& data, bool bSpawnPlayer);
	void load_level_file(string filePath, bool bSpawnPlayer);

	bool is_walkable(glm::vec2 posInGrid);

	std::vector<std::vector<Actor*>> actorGrid;
	std::vector<Actor*> currentLevel;
};