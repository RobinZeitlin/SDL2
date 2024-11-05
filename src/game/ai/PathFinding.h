#pragma once

#include <iostream>
#include <vector>
#include <glm.hpp>
#include <limits>

#include "PathNode.h"

class PathFinding {
public:
	const int MOVE_STRAIGHT_COST = 10;
	const int MOVE_DIAGONAL_COST = 14;

	std::vector<std::vector<PathNode*>> grid;
	std::vector<PathNode*> openList;
	std::vector<PathNode*> closedList;

	PathFinding(int width, int height);

	std::vector<PathNode*> FindPath(int startX, int startY, int endX, int endY);

	PathNode* GetNode(int x, int y) const;

	int CalculateDistanceCost(PathNode* a, PathNode* b);

	PathNode* GetLowestFCostNode(std::vector<PathNode*> pathNodeList);

	std::vector<PathNode*> CalculatePath(PathNode* endNode);
};