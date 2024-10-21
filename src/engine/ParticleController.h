#pragma once

#include <glm.hpp>

#include "Particle.h"

const int TOTAL_PARTICLES = 50;

class ParticleController
{
public:
	ParticleController(glm::vec2 pos, SDL_Texture* texture) {
		for (int i = 0; i < TOTAL_PARTICLES; i++)
		{
			if (texture == nullptr)
			{
				Debug::warning("Cant load particle texture");
			}

			auto newParticle = new Particle(pos, texture);
			particleList[i].push_back(newParticle);
		}
	}

	void render(SDL_Renderer* renderer) {
		for (int i = 0; i < TOTAL_PARTICLES; ++i) {
			for (auto particle : particleList[i]) {
				particle->render(renderer);
			}
		}
	}

private:
	std::vector<Particle*> particleList[TOTAL_PARTICLES];
};