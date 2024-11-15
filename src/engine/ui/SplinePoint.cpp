#include "SplinePoint.h"

#include "../../Game.h"

void SplinePoint::render_point()
{
	auto renderer = game->renderer;
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

	DebugDraw::draw_debug_sphere(renderer, glm::vec2(
		transform.position.x - game->camera->x,
		transform.position.y - game->camera->y),
		10, 10);

	render_handle(renderer);
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
