#pragma once

#include <iostream>
#include <array>
#include <glm.hpp>
#include <limits>

#include "PathNode.h"

class PathFinding {
public:
	const int MOVE_STRAIGHT_COST = 10;
	const int MOVE_DIAGONAL_COST = 14;

	std::array<std::array<PathNode*, 50>, 50> grid;
	std::vector<PathNode*> openList;
	std::vector<PathNode*> closedList;

	PathFinding();
	~PathFinding();

	std::vector<PathNode*> FindPath(int startX, int startY, int endX, int endY);
	std::vector<PathNode*> GetNeighbourList(PathNode* pathNode);
	std::vector<PathNode*> CalculatePath(PathNode* endNode);

	PathNode* GetNode(int x, int y) const;
	PathNode* GetLowestFCostNode(std::vector<PathNode*> pathNodeList);

	int CalculateDistanceCost(PathNode* a, PathNode* b);
};