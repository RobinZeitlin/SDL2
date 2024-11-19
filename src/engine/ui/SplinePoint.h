#pragma once

#include <SDL.h>

#include "glm.hpp"

#include "SplineHandles.h"

#include "../../game/components/location/Transform.h"

class SplinePoint
{
public:
	SplinePoint();
	~SplinePoint();

	void render_point();
	void render_handle(SDL_Renderer* renderer);

	void update_handles_and_rotation(glm::vec2 mousePos);

	void move_to(glm::vec2 newPos) { transform.position = newPos; }

	Transform transform;

	SplineHandles* handles = nullptr;
};