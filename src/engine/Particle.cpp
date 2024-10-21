#include "../engine/zmath.h"

#include "Particle.h"
#include "../Game.h"

Particle::Particle(glm::vec2 position, SDL_Texture* texture, int inScale, int spd, float dur)
{
	pos.x = position.x;
	pos.y = position.y;
	rot = rand() % 361;
	initialScale = rand() % inScale + 4;
	scale = initialScale;

	m_texture = texture;

	speed = spd;
	duration = dur;
	currentDuration = duration;
}

void Particle::render(SDL_Renderer* renderer)
{
	bDestroyed = currentDuration <= 0 || (currentDuration -= game->deltaTime, false);

	scale = initialScale * zmath::EaseOutCubicBounce(1 - (currentDuration / duration)) + 1;

	float radians = glm::radians(rot);
	glm::vec2 upVector = glm::vec2(std::cos(radians), std::sin(radians));

	pos += upVector * game->deltaTime * speed;
	
	SDL_Rect srcR = { 0, 0, 32, 32 };
	SDL_Rect destR = { pos.x - game->camera->x, pos.y - game->camera->y, scale, scale };

	SDL_RenderCopyEx(renderer, m_texture, &srcR, &destR, rot, NULL, SDL_FLIP_NONE);
}
