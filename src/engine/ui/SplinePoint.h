#pragma once

#include <SDL.h>

#include "glm.hpp"

class SplinePoint
{
public:
	glm::vec2 pos;
	float rotation;

	void render_point();
	void render_handle(SDL_Renderer* renderer);
};