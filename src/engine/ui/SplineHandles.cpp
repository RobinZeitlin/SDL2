#include "SplineHandles.h"

#include "../../Game.h"

glm::vec2 SplineHandles::get_handle_a_offset() {
	glm::vec2 offset = splinePoint->get_transform_up() * distance;
	return offset;
}

glm::vec2 SplineHandles::get_handle_b_offset() {
	glm::vec2 offset = -splinePoint->get_transform_up() * distance;
	return offset;
}