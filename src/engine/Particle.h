#pragma once

#include <glm.hpp>
#include <SDL.h>
#include <random>

#include "../game/components/location/Transform.h"

class Particle
{
public:
	Particle(glm::vec2 position, SDL_Texture* texture, int inScale, int spd, float dur);

	void render(SDL_Renderer* renderer);

	bool isDestroyed() { 
		return bDestroyed; 
	};

	bool bDestroyed = false;

private:
	SDL_Texture* m_texture;
	
	glm::vec2 pos;

	float rot;
	float scale;
	float initialScale;

	float speed;
	float duration;
	float currentDuration;
};