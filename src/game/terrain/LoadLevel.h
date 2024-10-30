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

	std::vector<Actor*> currentLevel;

	void add_actor(Actor* actor) { currentLevel.push_back(actor); }

	void clear_current_level() {

		if (currentLevel.size() == 0)
			return;

		for (auto actor : currentLevel)
		{
			actor->destroy();
			std::cout << "Destroyed" << std::endl;
		}
	}


	void spawn_level(const std::vector<std::string>& data, bool bSpawnPlayer)
	{
		bool shouldExit = false;

		for (int i = 0; i < data.size() && !shouldExit; ++i) 
		{
			for (int j = 0; j < data[i].length() && !shouldExit; ++j) 
			{
				glm::vec2 position(j * 32.0f, i * 32.0f);
				glm::vec2 scale(32.0f, 32.0f);
				Actor* actor = nullptr;

				switch (data[i][j])	{
				case 'D':
				    actor = new Block();
					game->spawnActor(actor, position, scale);
					break;

				case 'G':
					actor = new GrassBlock();
					game->spawnActor(actor, position, scale);
					break;

				case 'S':
				    actor = new Stairs();
					game->spawnActor(actor, position, scale);
					break;

				case 'E':
				    actor = new Enemy();
					game->spawnActor(actor, position, scale);
					break;

				case 'P':
					if(bSpawnPlayer)
					game->spawnPlayer(position);
					break;

				case 'Q':
					shouldExit = true;
					break;

				default:
					break;
				}

				if(actor != nullptr)
				add_actor(actor);
			}
		}
	}

	void load_level_file(string filePath, bool bSpawnPlayer)
	{
		ifstream file(filePath + ".csv");
		if (!file.is_open()) {
			Debug::log("File did not open correctly.");
			return;
		}

		vector<string> data;
		string line;

		while (getline(file, line)) {
			data.push_back(line);
		}

		file.close();

		clear_current_level();
		spawn_level(data, bSpawnPlayer);
	}
};