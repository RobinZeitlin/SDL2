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

enum class Render_Layer
{
	None,
	Background,
	Enviorement,
	Entities,
	CollisionLayer,
	UI,
	LayerCount
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
	Render_Layer render_layer = Render_Layer::None;
};