#pragma once

class PathNode {
public:
	int x;
	int y;

	int gCost;
	int hCost;
	int fCost;

	PathNode* cameFromNode;

	void CalculateFCost() {
		fCost = gCost + hCost;
	}
};