#pragma once

#include <glm.hpp>
#include <SDL.h>
#include <random>

#include "../game/components/location/Transform.h"

class Particle
{
public:
	Particle(glm::vec2 position, SDL_Texture* texture);

	void render(SDL_Renderer* renderer);

private:
	SDL_Texture* m_texture;

	float velX, velY;
	float rot;

	glm::vec2 pos;

	float speed;
};