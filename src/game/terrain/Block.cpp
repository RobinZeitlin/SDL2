#include "Block.h"

Block::Block()
{
	texture = textureManager->getTexture("cube");
}

void Block::render(SDL_Renderer* renderer)
{
	SDL_Rect srcR = { 0, 0, 32, 32 };

	SDL_Rect destR = { transform.position.x * 32, transform.position.y * 32, 32, 32 };

	SDL_RenderCopy(renderer, texture, &srcR, &destR);
}
