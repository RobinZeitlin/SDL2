#pragma once

#include "../components/location/Transform.h"
#include "../../engine/TextureManager.h"

#include "glm.hpp"
#include "SDL_image.h"

#include "../../Camera.h"

class Actor
{
public:
	Actor();
	~Actor();

	virtual void update() {};
	virtual void render(SDL_Renderer* renderer, Camera* camera) {};

	SDL_Texture* texture = nullptr;
	Transform transform;
};