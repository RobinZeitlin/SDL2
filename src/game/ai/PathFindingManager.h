#pragma once

#include "PathFinding.h"

#include <SDL.h>
#include <queue>

class PathFindingManager
{
public:
	PathFindingManager(int width, int height) {
		pathFinding = new PathFinding();
	}

	~PathFindingManager() {
		delete pathFinding;
	}

	std::queue<glm::vec2> get_path_from_to(glm::vec2 from, glm::vec2 to);

private: 
	PathFinding* pathFinding;
};