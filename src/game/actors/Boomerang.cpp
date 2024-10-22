#include "Boomerang.h"
#include "../../Game.h"
#include "../../engine/DebugDraw.h"

Boomerang::Boomerang()
{
	texture = textureManager->getTexture("boomerang");

	collision_channel = Collision_Channel::P_Projectile;
	render_layer = Render_Layer::Entities;

	game->layers[static_cast<size_t>(render_layer)].push_back(this);
}

void Boomerang::update(float dt)
{
	transform.position += (transform.get_transform_up() * projectileSpeed) * dt;

	visualRotation += 600.0f * dt;

	check_overlap();
}

void Boomerang::render(SDL_Renderer* renderer, Camera* camera)
{
	SDL_Rect srcR = { 0, 0, 32, 32 };

	SDL_Rect destR = { transform.position.x - camera->x, transform.position.y - camera->y, 36, 36 };

	SDL_RenderCopyEx(renderer, texture, &srcR, &destR, visualRotation, NULL, SDL_FLIP_NONE);
}

void Boomerang::check_overlap()
{
	Actor* hit_ground_actor = game->get_overlapping_actor(this, Collision_Channel::Ground);
	if (hit_ground_actor != nullptr)
	{
		auto particleCtrl = new ParticleController(transform.position + (transform.scale * 0.5f), textureManager->getTexture("effect2"), 30, 25, 250, 0.25f);
		game->particleControllers.push_back(particleCtrl);

		auto particleCtrl2 = new ParticleController(transform.position + (transform.scale * 0.5f), textureManager->getTexture("effect"), 1, 80, 0, 0.5f);
		game->particleControllers.push_back(particleCtrl2);

		destroy();
	}
};
