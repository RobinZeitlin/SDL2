#include "PathFindingManager.h"

#include "../../engine/DebugDraw.h"

#include "../../Game.h"

std::queue<glm::vec2> PathFindingManager::get_path_from_to(glm::vec2 from, glm::vec2 to)
{
    if (!pathFinding->is_on_grid(to)) return std::queue<glm::vec2>();

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
