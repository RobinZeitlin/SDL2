#include "Enemy.h"

#include "../../Game.h"

#include "../../engine/Linetrace.h"
#include "../../engine/LineHit.h"

Enemy::Enemy()
{
	texture = textureManager->getTexture("enemy");

	collision_channel = Collision_Channel::Enemy;
	render_layer = Render_Layer::Entities;

	game->layers[static_cast<size_t>(render_layer)].push_back(this);
}

void Enemy::update(float dt)
{
	if (game->bEditor || game->player == nullptr) return;

	glm::vec2 playerPos = game->player->transform.position;
	float distanceToPlayer = transform.get_distance(transform.position, game->player->transform.position);

	if (distanceToPlayer - 16 < proximityRange) {
		if (pathPositions.empty() || glm::distance(lastPlayerPos, playerPos) > 10.0f) {
			lastPlayerPos = playerPos;
			pathPositions = game->pathFindingManager->get_path_from_to(
				transform.position / glm::vec2(32),
				playerPos / glm::vec2(32)
			);
		}

		if (pathPositions.size() > 0) {
			transform.position += (-transform.get_transform_up() * walkingSpeed) * dt;

			glm::vec2 direction = transform.get_direction_towards(transform.position, pathPositions.front());

			float angle = std::atan2(direction.y, direction.x);

			transform.rotation.x = glm::degrees(angle);

			float distanceToNextGoal = transform.get_distance(transform.position, pathPositions.front());
			if (distanceToNextGoal < 1) {
				pathPositions.pop();
			}
		}
	}
	check_overlap();
}

void Enemy::render(SDL_Renderer* renderer, Camera* camera)
{
	SDL_Rect srcR = { 0, 0, 32, 32 };
	SDL_Rect destR = { (transform.position.x) - camera->x, (transform.position.y) - camera->y, 32, 32 };

	SDL_RenderCopyEx(renderer, texture, &srcR, &destR, transform.rotation.x, NULL, SDL_FLIP_NONE);

	if (game->player == nullptr) return;

	float distanceToPlayer;

	std::vector<glm::vec2> positions;
	std::queue<glm::vec2> pathCopy = pathPositions;

	while (!pathCopy.empty()) {
		positions.push_back(pathCopy.front());
		pathCopy.pop();
	}

	for (size_t i = 1; i < positions.size(); ++i) {
		const glm::vec2& lastPos = positions[i - 1];
		const glm::vec2& pos = positions[i];

		SDL_Color color = GIZMO_COLOR;
		SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
		SDL_RenderDrawLineF(renderer, lastPos.x - game->camera->x, lastPos.y - game->camera->y, pos.x - game->camera->x, pos.y - game->camera->y);
	}

	if (!game->bEditor)
		distanceToPlayer = transform.get_distance(transform.position, game->player->transform.position);
	else
		distanceToPlayer = 1000.0f;

	if (distanceToPlayer - 16 > proximityRange) {
		SDL_Color color = GIZMO_COLOR;

		SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

		DebugDraw::draw_debug_sphere(renderer, glm::vec2(
			((transform.position.x + transform.scale.x / 2) - camera->x),
			((transform.position.y + transform.scale.y / 2) - camera->y)),
			proximityRange, 20);

		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	}
}

void Enemy::check_overlap()
{
	Actor* hit_actor = game->get_overlapping_actor(this, Collision_Channel::P_Projectile);
	if (hit_actor != nullptr)
	{
		auto particleCtrl = std::make_unique<ParticleController>(transform.position, textureManager->getTexture("enemy"), 30, 12, 200, 0.5f);
		game->particleControllers.push_back(std::move(particleCtrl));

		auto particleCtrl2 = std::make_unique<ParticleController>(transform.position, textureManager->getTexture("effectred"), 1, 100, 0, 0.5f);
		game->particleControllers.push_back(std::move(particleCtrl2));
		destroy();
	}
}
