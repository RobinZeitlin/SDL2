#pragma once

#include "glm.hpp"

class Transform
{
public:
	glm::vec2 position;
	glm::vec2 scale;
	glm::vec2 rotation;

	glm::vec2 get_direction_towards(glm::vec2 posA, glm::vec2 posB)
	{
		glm::vec2 eulerAngleDirection = glm::normalize(posA - posB);
		return eulerAngleDirection;
	}

	glm::vec2 get_transform_up()
	{
		float radians = glm::radians(rotation.x);
		glm::vec2 upVector = glm::vec2(std::cos(radians), std::sin(radians));

		return upVector;
	}

	glm::vec2 get_transform_right()
	{
		float radians = glm::radians(rotation.x);
		glm::vec2 rightVector = glm::vec2(-std::sin(radians), std::cos(radians)); 

		return rightVector;
	}
};