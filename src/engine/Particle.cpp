#include "Particle.h"
#include "../Game.h"

Particle::Particle(glm::vec2 position, SDL_Texture* texture)
{
	pos.x = position.x;
	pos.y = position.y;
	rot = rand() % 361;
	m_texture = texture;

	speed = 500.0f;
}

void Particle::render(SDL_Renderer* renderer)
{
	float radians = glm::radians(rot);
	glm::vec2 upVector = glm::vec2(std::cos(radians), std::sin(radians));

	pos += upVector * game->deltaTime * speed;
	
	SDL_Rect srcR = { 0, 0, 32, 32 };
	SDL_Rect destR = { pos.x - game->camera->x, pos.y - game->camera->y, 12, 12 };

	SDL_RenderCopyEx(renderer, m_texture, &srcR, &destR, rot, NULL, SDL_FLIP_NONE);
}
