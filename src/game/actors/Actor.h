#pragma once

#include "../components/location/Transform.h"
#include "../../engine/TextureManager.h"

#include "glm.hpp"
#include "SDL_image.h"

#include "../../Camera.h"

enum class Collision_Channel
{
	None,
	Default,
	Ignore,
	Ground,
	Player,
	P_Projectile,
	Enemy,
};

class Actor
{
public:
	Actor();
	~Actor();

	virtual void update(float dt) {};
	virtual void render(SDL_Renderer* renderer, Camera* camera) {};

	std::string actorName;

	SDL_Texture* texture = nullptr;
	Transform transform;

	Collision_Channel collision_channel = Collision_Channel::None;
};