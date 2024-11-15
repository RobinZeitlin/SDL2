#pragma once

#include "Actor.h"
#include "../../engine/DebugDraw.h"

#include <queue>

class Camera;

class Enemy : public Actor
{
public:
	Enemy();

	void update(float dt);
	void render(SDL_Renderer* renderer, Camera* camera) override;

	void check_overlap();

private:
	float walkingSpeed = 250;
	float proximityRange = 250;

	std::queue<glm::vec2> pathPositions;

	glm::vec2 lastPlayerPos = glm::vec2(0);
};