#pragma once

#include <SDL.h>

#include "../../game/components/location/Transform.h"
#include "glm.hpp"

class SplinePoint
{
public:
	Transform transform;
	float rotation;

	SplinePoint();

	void render_point();
	void render_handle(SDL_Renderer* renderer);
};