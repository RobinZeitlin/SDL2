#include "PathFinding.h"

PathFinding::PathFinding(int width, int height)
{
	grid.resize(height);
	for (int i = 0; i < height; ++i) {
		grid[i].resize(width, nullptr);
	}
}

std::vector<PathNode*> PathFinding::FindPath(int startX, int startY, int endX, int endY)
{
	PathNode* startNode = GetNode(startX, startY);
	PathNode* endNode = GetNode(endX, endY);

	openList.push_back(startNode);

	for (int x = 0; x < grid.size(); x++)
	{
		for (int y = 0; y < grid[x].size(); y++)
		{
			auto pathNode = grid[x][y];

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
		if (currentNode == endNode) {
			return CalculatePath(endNode);
		}
	}
}
 
std::vector<PathNode*> PathFinding::CalculatePath(PathNode* endNode)
{
	return std::vector<PathNode*>();
}

PathNode* PathFinding::GetNode(int x, int y) const {
	if (y >= 0 && y < grid.size() && x >= 0 && x < grid[y].size()) {
		return grid[y][x];
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