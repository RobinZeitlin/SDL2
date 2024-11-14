#include "ParticleController.h"

ParticleController::ParticleController(glm::vec2 pos, SDL_Texture* texture, int maxParticles, int inScale, int spd, float dur)
{
	for (int i = 0; i < maxParticles; i++) {
		if (i >= MAX_PARTICLES)
			break;

		if (texture == nullptr) return;

		auto newParticle = std::make_unique<Particle>(pos, texture, inScale, spd, dur);
		particleList[i].push_back(std::move(newParticle));
	}
}

void ParticleController::render(SDL_Renderer* renderer)
{
	for (int i = 0; i < MAX_PARTICLES; ++i) {
		for (auto it = particleList[i].begin(); it != particleList[i].end();) {
			Particle* particle = it->get();

			if (particle == nullptr) {
				++it;
				continue;
			}

			if (particle->isDestroyed()) {
				it = particleList[i].erase(it);
				continue;
			}

			particle->render(renderer);
			++it;
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
