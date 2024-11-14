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

	static const int gridSize = 45;

	std::array<std::array<PathNode*, gridSize>, gridSize> grid;
	std::vector<PathNode*> openList;
	std::vector<PathNode*> closedList;

	PathFinding();
	~PathFinding();

	std::vector<PathNode*> FindPath(int startX, int startY, int endX, int endY);
	std::vector<PathNode*> GetNeighbourList(PathNode* pathNode);
	std::vector<PathNode*> CalculatePath(PathNode* endNode);

	PathNode* GetNode(int x, int y) const;
	PathNode* GetLowestFCostNode(std::vector<PathNode*> pathNodeList);

	bool is_on_grid(glm::vec2 posA);

	int CalculateDistanceCost(PathNode* a, PathNode* b);
};