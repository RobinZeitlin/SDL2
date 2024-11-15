#include "SplinePoint.h"

#include "../../Game.h"

SplinePoint::SplinePoint()
{
	transform.scale.x = 10.0f;
}

void SplinePoint::render_point()
{
	auto renderer = game->renderer;

	if (game->levelEditor->selectedSplinePoint == this) {
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

		DebugDraw::draw_debug_sphere(renderer, glm::vec2(
			transform.position.x - game->camera->x,
			transform.position.y - game->camera->y),
			transform.scale.x * 1.2f, 10);

		render_handle(renderer);
	}
	else {

		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

		DebugDraw::draw_debug_sphere(renderer, glm::vec2(
			transform.position.x - game->camera->x,
			transform.position.y - game->camera->y),
			transform.scale.x, 10);
	}
}

void SplinePoint::render_handle(SDL_Renderer* renderer) {
	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);

	SDL_RenderDrawLineF(renderer,
		transform.position.x - game->camera->x,
		transform.position.y - game->camera->y,
		transform.position.x - game->camera->x,
		transform.position.y - game->camera->y - 50);

	SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);

	DebugDraw::draw_debug_sphere(renderer, glm::vec2(
		transform.position.x - game->camera->x,
		transform.position.y - game->camera->y - 50),
		5, 10);
}
