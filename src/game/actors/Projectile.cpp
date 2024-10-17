#include "Projectile.h"

#include "../../Game.h"

Projectile::Projectile()
{
	texture = textureManager->getTexture("projectile");

	collision_channel = Collision_Channel::P_Projectile;

	actorName = "Bullet";

	projectileSpeed = 700;
}

void Projectile::update(float dt)
{
	transform.position += (transform.get_transform_up() * projectileSpeed) * dt;

	check_overlap();
}

void Projectile::render(SDL_Renderer* renderer, Camera* camera)
{
	SDL_Rect srcR = { 0, 0, 32, 32 };

	SDL_Rect destR = { transform.position.x - camera->x, transform.position.y - camera->y, 32, 32 };

	SDL_RenderCopyEx(renderer, texture, &srcR, &destR, transform.rotation.x, NULL, SDL_FLIP_NONE);

	// gizmos

	const int gizmoMultiplier = 40;

	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);

	glm::vec2 upVector = glm::vec2(transform.position.x + transform.get_transform_up().x * gizmoMultiplier, transform.position.y + transform.get_transform_up().y * gizmoMultiplier);
	SDL_RenderDrawLine(renderer, transform.position.x - camera->x + 16, transform.position.y - camera->y + 16, upVector.x - camera->x + 16, upVector.y - camera->y + 16);

	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

	glm::vec2 rightVector = glm::vec2(transform.position.x + transform.get_transform_right().x * gizmoMultiplier, transform.position.y + transform.get_transform_right().y * gizmoMultiplier);
	SDL_RenderDrawLine(renderer, transform.position.x - camera->x + 16, transform.position.y - camera->y + 16, rightVector.x - camera->x + 16, rightVector.y - camera->y + 16);

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}


void Projectile::check_overlap()
{
	glm::vec2 previous_position = transform.position;

	Actor* hit_actor = game->get_overlapping_actor(this, Collision_Channel::Ground);
	if (hit_actor != nullptr)
	{
		std::cout << "hit" << std::endl;
	}
}