#pragma once

#include <glm.hpp>

#include "Particle.h"

const int TOTAL_PARTICLES = 1000;

class ParticleController
{
public:
	ParticleController(glm::vec2 pos, SDL_Texture* texture, int maxParticles = 25, int inScale = 5, int spd = 400, float dur = 0.2f) {
		for (int i = 0; i < maxParticles; i++) {
			if (i >= TOTAL_PARTICLES)
				break;

			if (texture == nullptr) {
				Debug::warning("Cant load particle texture");
			}

			auto newParticle = new Particle(pos, texture, inScale, spd, dur);
			particleList[i].push_back(newParticle);
		}
	}

	void render(SDL_Renderer* renderer) {
		for (int i = 0; i < TOTAL_PARTICLES; ++i) {
			for (auto particle : particleList[i]) {

				if(particle == nullptr)
					return;

				if (particle->isDestroyed()) {
					
					particleList->at(i) = nullptr;
					delete particle;

					return;
				}

				particle->render(renderer);
			}
		}
	}

	bool isEmpty() {
		for (int i = 0; i < TOTAL_PARTICLES; ++i) {
			for (auto particle : particleList[i]) {
				if (particle != nullptr && !particle->isDestroyed()) {
					return false;
				}
			}
		}
		return true;
	}

private:
	std::vector<Particle*> particleList[TOTAL_PARTICLES];
};