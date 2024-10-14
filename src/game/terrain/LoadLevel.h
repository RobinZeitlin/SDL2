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
#include "../terrain/Enemy.h"

using namespace std;

class LoadLevel
{
public:
	void spawn_level(const std::vector<std::string>& data)
	{
		bool shouldExit = false;

		for (int i = 0; i < data.size() && !shouldExit; ++i) 
		{
			for (int j = 0; j < data[i].length() && !shouldExit; ++j) 
			{
				glm::vec2 position(j * 32.0f, i * 32.0f);
				glm::vec2 scale(32.0f, 32.0f);

				switch (data[i][j])	{
				case 'D':
						game->spawnActor(new Block(), position, scale);
					break;

				case 'G':
					game->spawnActor(new GrassBlock(), position, scale);
					break;

				case 'S':
					game->spawnActor(new Stairs(), position, scale);
					break;

				case 'E':
					game->spawnActor(new Enemy(), position, scale);
					break;

				case 'P':
					game->spawnPlayer(position);
					break;

				case 'Q':
					shouldExit = true;
					break;

				default:
					break;
				}
			}
		}
	}

	void load_level_file(string filePath)
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

		spawn_level(data);
	}
};