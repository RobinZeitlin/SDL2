#pragma once

#include "../components/location/Transform.h"
#include "../../engine/TextureManager.h"

#include "glm.hpp"
#include "SDL_image.h"

class Actor
{
public:
	Actor();
	~Actor();

	virtual void update();
	virtual void render(SDL_Renderer* renderer);

	SDL_Texture* texture;
	Transform transform;
};