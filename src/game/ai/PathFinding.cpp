#include "PathFinding.h"

PathFinding::PathFinding(int width, int height) {
    grid.resize(height);
    for (int y = 0; y < height; ++y) {
        grid[y].resize(width);
        for (int x = 0; x < width; ++x) {
            grid[y][x] = new PathNode(x, y);
        }
    }
}

std::vector<PathNode*> PathFinding::FindPath(int startX, int startY, int endX, int endY)
{
    PathNode* startNode = GetNode(startX, startY);
    PathNode* endNode = GetNode(endX, endY);

    if (startNode == nullptr || endNode == nullptr) {
        std::cout << "Error: Missing start or end node at (" << startX << ", " << startY
            << ") or (" << endX << ", " << endY << ")" << std::endl;
        return std::vector<PathNode*>();
    }

    openList.clear();
    closedList.clear();
    openList.push_back(startNode);

    for (int x = 0; x < grid.size(); x++) {
        for (int y = 0; y < grid[x].size(); y++) {
            PathNode* pathNode = grid[x][y];
            if (pathNode == nullptr) {
                std::cout << "Error: Found nullptr in grid at (" << x << ", " << y << ")" << std::endl;
                continue;
            }
            pathNode->gCost = std::numeric_limits<int>::max();
            pathNode->CalculateFCost();
            pathNode->cameFromNode = nullptr;
        }
    }

    startNode->gCost = 0;
    startNode->hCost = CalculateDistanceCost(startNode, endNode);
    startNode->CalculateFCost();

    while (!openList.empty()) {
        PathNode* currentNode = GetLowestFCostNode(openList);
        if (currentNode == nullptr) {
            std::cout << "Error: GetLowestFCostNode returned nullptr" << std::endl;
            return std::vector<PathNode*>();
        }

        if (currentNode == endNode) {
            return CalculatePath(endNode);
        }

        openList.erase(std::remove(openList.begin(), openList.end(), currentNode), openList.end());
        closedList.push_back(currentNode);

        for (PathNode* neighbourNode : GetNeighbourList(currentNode)) {
            if (neighbourNode == nullptr) {
                std::cout << "Error: Found nullptr in neighbor list of node at ("
                    << currentNode->x << ", " << currentNode->y << ")" << std::endl;
                continue;
            }
            if (std::find(closedList.begin(), closedList.end(), neighbourNode) != closedList.end())
                continue;

            int tentativeGCost = currentNode->gCost + CalculateDistanceCost(currentNode, neighbourNode);

            if (tentativeGCost < neighbourNode->gCost) {
                neighbourNode->cameFromNode = currentNode;
                neighbourNode->gCost = tentativeGCost;
                neighbourNode->hCost = CalculateDistanceCost(neighbourNode, endNode);
                neighbourNode->CalculateFCost();

                if (std::find(openList.begin(), openList.end(), neighbourNode) == openList.end()) {
                    openList.push_back(neighbourNode);
                }
            }
        }
    }

    return std::vector<PathNode*>();
}

 
std::vector<PathNode*> PathFinding::GetNeighbourList(PathNode* currentNode)
{
	std::vector<PathNode*> neighbourList;

	if (currentNode->x - 1 >= 0) {
		// left
		neighbourList.push_back(GetNode(currentNode->x - 1, currentNode->y));
		// left down
		if (currentNode->y - 1 >= 0) neighbourList.push_back(GetNode(currentNode->x - 1, currentNode->y - 1));
		// left up
		if (currentNode->y + 1 < grid.size()) neighbourList.push_back(GetNode(currentNode->x - 1, currentNode->y + 1));
	}
	if (currentNode->x + 1 < grid[0].size()) {
		// right
		neighbourList.push_back(GetNode(currentNode->x + 1, currentNode->y));
		// right down
		if (currentNode->y - 1 >= 0) neighbourList.push_back(GetNode(currentNode->x + 1, currentNode->y - 1));
		// right up
		if (currentNode->y - 1 < grid.size()) neighbourList.push_back(GetNode(currentNode->x + 1, currentNode->y + 1));
	}
	// down
	if (currentNode->y - 1 >= 0) neighbourList.push_back(GetNode(currentNode->x, currentNode->y - 1));
	// up
	if (currentNode->y + 1 < grid.size()) neighbourList.push_back(GetNode(currentNode->x, currentNode->y + 1));

	return neighbourList;
}

std::vector<PathNode*> PathFinding::CalculatePath(PathNode* endNode)
{
	std::vector<PathNode*> path;
	path.push_back(endNode);
	PathNode* currentNode = endNode;
	while (currentNode->cameFromNode != nullptr) {
		path.push_back(currentNode->cameFromNode);
		currentNode = currentNode->cameFromNode;
	}
	std::reverse(path.begin(), path.end());

	return path;
}

PathNode* PathFinding::GetNode(int x, int y) const {
    if (y >= 0 && y < grid.size() && x >= 0 && x < grid[y].size()) {
        PathNode* node = grid[y][x];
        if (node) {
            std::cout << "Retrieved node at (" << x << ", " << y << ")" << std::endl;
            return node;
        }
        else {
            std::cout << "No node found at (" << x << ", " << y << ")" << std::endl;
        }
    }
    else {
        std::cout << "Coordinates (" << x << ", " << y << ") are out of grid bounds." << std::endl;
    }
    return nullptr;
}


int PathFinding::CalculateDistanceCost(PathNode* a, PathNode* b)
{
	int xDistance = glm::abs(a->x - b->x);
	int yDistance = glm::abs(a->y - b->y);
	int remaining = glm::abs(xDistance - yDistance);
	return MOVE_DIAGONAL_COST * glm::min(xDistance, yDistance) + MOVE_STRAIGHT_COST * remaining;
}

PathNode* PathFinding::GetLowestFCostNode(std::vector<PathNode*> pathNodeList)
{
	PathNode* lowestFCostNode = pathNodeList[0];
	for (int i = 1; i < pathNodeList.size(); i++) {
		if (pathNodeList[i]->fCost < lowestFCostNode->fCost) {
			lowestFCostNode = pathNodeList[i];
		}
	}

	return lowestFCostNode;
}