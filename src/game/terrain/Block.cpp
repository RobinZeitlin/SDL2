#include "Block.h"

Block::Block()
{
	texture = textureManager->getTexture("cube");
}

void Block::render(SDL_Renderer* renderer, Camera* camera)
{
	SDL_Rect srcR = { 0, 0, 32, 32 };

	SDL_Rect destR = { (transform.position.x * 32) - camera->x, (transform.position.y * 32) - camera->y, 32, 32 };

	SDL_RenderCopy(renderer, texture, &srcR, &destR);
}
