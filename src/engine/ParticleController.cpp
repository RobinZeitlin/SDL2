#include "ParticleController.h"

ParticleController::ParticleController(glm::vec2 pos, SDL_Texture* texture, int maxParticles, int inScale, int spd, float dur)
{
	for (int i = 0; i < maxParticles; i++) {
		if (i >= MAX_PARTICLES)
			break;

		if (texture == nullptr) return;

		auto newParticle = new Particle(pos, texture, inScale, spd, dur);
		particleList[i].push_back(newParticle);
	}
}

void ParticleController::render(SDL_Renderer* renderer)
{
	for (int i = 0; i < MAX_PARTICLES; ++i) {
		for (auto particle : particleList[i]) {
			if (particle == nullptr)
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

bool ParticleController::is_empty()
{
	for (const auto& particles : particleList) {
		for (const auto& particle : particles) {
			if (particle != nullptr && !particle->isDestroyed()) {
				return false;
			}
		}
	}
	return true;
}
