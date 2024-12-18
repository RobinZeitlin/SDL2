#pragma once

#include <glm.hpp>

#include "Particle.h"

const int MAX_PARTICLES = 200;

class ParticleController
{
public:
	ParticleController(glm::vec2 pos, SDL_Texture* texture, int maxParticles = 25, int inScale = 5, int spd = 400, float dur = 0.2f);
	~ParticleController() = default;
	void render(SDL_Renderer* renderer);

	bool is_empty();

private:
	std::vector<std::unique_ptr<Particle>> particleList[MAX_PARTICLES];
};