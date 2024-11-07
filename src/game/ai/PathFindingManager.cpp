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
            std::cout << "Found Path at:" << std::endl;

            for (auto* pathNode : path) {
                if (pathNode != nullptr) {
                    std::cout << "X: " << pathNode->x << " Y: " << pathNode->y << std::endl;
                    positions.push({ pathNode->x, pathNode->y });
                }
            }
        }
        else
        {
            std::cout << "No path found from (" << from.x << ", " << from.y << ") to (" << to.x << ", " << to.y << ")" << std::endl;
        }
    }
    else
    {
        std::cout << "PathFinding instance is nullptr." << std::endl;
    }

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
