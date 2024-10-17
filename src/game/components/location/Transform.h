#pragma once

#include "glm.hpp"

class Transform
{
public:
	glm::vec2 position;
	glm::vec2 scale;
	float rotation;

	glm::vec2 get_direction_towards(glm::vec2 posA, glm::vec2 posB)
	{
		glm::vec2 eulerAngleDirection = glm::normalize(posA - posB);
		return eulerAngleDirection;
	}
};