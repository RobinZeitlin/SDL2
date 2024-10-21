#pragma once

#include <glm.hpp>

#include "../game/components/location/Transform.h"

struct AABB
{
	static AABB from_position_size(Transform transform);

	AABB(glm::vec2 in_min, glm::vec2 in_max) : min(in_min), max(in_max) { }

	glm::vec2 min;
	glm::vec2 max;
}; 

bool aabb_overlap(AABB a, AABB b);
