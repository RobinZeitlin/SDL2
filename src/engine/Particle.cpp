#include "Particle.h"
#include "../Game.h"

Particle::Particle(glm::vec2 position, SDL_Texture* texture)
{
	X = position.x;
	Y = position.y;
	
	velX = static_cast<float>(rand() % 200 - 100);
    velY = static_cast<float>(rand() % 200 - 100);
	
	if (velX == 0) velX = 1;
	if (velY == 0) velY = 1;
	
	Rot = rand() % 361;
	m_texture = texture;
}

void Particle::render(SDL_Renderer* renderer)
{
	X += velX * game->deltaTime;
	Y += velY * game->deltaTime;

	SDL_Rect srcR = { 0, 0, 32, 32 };
	SDL_Rect destR = { X - game->camera->x, Y - game->camera->y, 16, 16 };

	SDL_RenderCopyEx(renderer, m_texture, &srcR, &destR, Rot, NULL, SDL_FLIP_NONE);
}
