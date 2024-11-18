#pragma once

#include <glm.hpp>

#include "../../game/components/location/Transform.h"

class SplineHandles {
public:
	SplineHandles(Transform* sPoint) 
		: splinePoint(sPoint) 
	{ };

	Transform* splinePoint;

	float distance = 80.0f;

	glm::vec2 get_handle_a_offset();
	glm::vec2 get_handle_b_offset();
};