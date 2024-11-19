#pragma once

#include <glm.hpp>

class Actor;

class Camera {
public:
	Camera(float posX, float posY, float width, float height);

	float x, y;
	float width, height;

	void updateCamera(glm::vec2 pos, float deltaTime);
	glm::vec2 get_pos() { return glm::vec2(x, y); }
};