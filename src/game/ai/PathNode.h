#pragma once

class PathNode {
public:

	PathNode(int posX, int posY) : x(posX), y(posY) { };

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