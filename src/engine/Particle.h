#pragma once

#include <glm.hpp>
#include <SDL.h>
#include <random>

class Particle
{
public:
	Particle(glm::vec2 position, SDL_Texture* texture);

	void render(SDL_Renderer* renderer);

	int velX, velY;
	int X, Y;
	int Rot;

private:
	SDL_Texture* m_texture;
};