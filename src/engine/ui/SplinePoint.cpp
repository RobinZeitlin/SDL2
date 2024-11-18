#include "SplinePoint.h"

#include "../../Game.h"
#include "../../Camera.h"

SplinePoint::SplinePoint() {
	transform.scale.x = 10.0f;
	transform.rotation = glm::vec2(270, 0);

	handles = new SplineHandles(&this->transform);
}

SplinePoint::~SplinePoint()
{
	delete handles;
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
void SplinePoint::render_handle(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

	glm::vec2 cameraPos = glm::vec2(game->camera->x, game->camera->y);

	DebugDraw::draw_debug_sphere(renderer, 
		transform.position + handles->get_handle_a_offset() - glm::vec2(game->camera->x, game->camera->y),
		transform.scale.x * 0.6f, 10);

	DebugDraw::draw_debug_sphere(renderer, 
		transform.position + handles->get_handle_b_offset() - glm::vec2(game->camera->x, game->camera->y),
		transform.scale.x * 0.6f, 10);

	glm::vec2 offsetB = transform.position + handles->get_handle_b_offset() - cameraPos;
	SDL_RenderDrawLineF(renderer,
		transform.position.x - cameraPos.x,
		transform.position.y - cameraPos.y,
		offsetB.x,
		offsetB.y);

	glm::vec2 offsetA = transform.position + handles->get_handle_a_offset() - cameraPos;
	SDL_RenderDrawLineF(renderer,
		transform.position.x - cameraPos.x,
		transform.position.y - cameraPos.y,
		offsetA.x,
		offsetA.y);
}

void SplinePoint::update_handles_and_rotation(glm::vec2 mousePos) {
	glm::vec2 thisPointPos = transform.position;
	float distance = transform.get_distance(thisPointPos, mousePos);

	glm::vec2 direction = glm::normalize(mousePos - thisPointPos);
	float angle = std::atan2(direction.y, direction.x);
	transform.rotation.x = glm::degrees(angle);

	handles->distance = distance;
}

