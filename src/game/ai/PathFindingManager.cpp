#include "PathFindingManager.h"

#include "../../engine/DebugDraw.h"

#include "../../Game.h"

std::queue<glm::vec2> PathFindingManager::get_path_from_to(glm::vec2 from, glm::vec2 to)
{
    std::queue<glm::vec2> positions;
    if (pathFinding != nullptr)
    {
        std::vector<PathNode*> path = pathFinding->FindPath(from.x, from.y, to.x, to.y);

        if (!path.empty()) {

            for (auto* pathNode : path) {
                if (pathNode != nullptr) {
                    positions.push({ pathNode->x * 32, pathNode->y * 32 });
                }
            }
        }

    }

    if (positions.size() > 1)
        positions.pop();

    return positions;
}

void PathFindingManager::render_grid(SDL_Renderer* renderer)
{
	/*for (int y = 0; y < pathFinding->grid.size(); ++y) {
		for (int x = 0; x < pathFinding->grid[y].size(); ++x) {
			int resolution = 32;
			glm::vec2 position(x * 32, y * 32);
			float radius = resolution / 2;

			SDL_SetRenderDrawColor(renderer, 0, 155, 255, 255);

			DebugDraw::draw_debug_sphere(renderer, (position - glm::vec2(game->camera->x, game->camera->y)) - glm::vec2(resolution / 2), radius, 6);
		}
	}*/
}
