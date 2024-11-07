#pragma once

#include "PathFinding.h"
#include <SDL.h>
#include <queue>

class PathFindingManager
{
public:
	PathFindingManager(int width, int height) {
		pathFinding = new PathFinding(width, height);
	}

	std::queue<glm::vec2> get_path_from_to(glm::vec2 from, glm::vec2 to);
	void render_grid(SDL_Renderer* renderer);

private: 
	PathFinding* pathFinding;
};