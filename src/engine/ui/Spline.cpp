#include "Spline.h"

#include <cmath>

#include "../../Game.h"
#include "../DebugDraw.h"

void Spline::render_debug(SDL_Renderer* renderer)
{
    for (auto point : splinePoints) {
        point->render_point();
    }

    if (splinePoints.size() > 1) {
        interpolateAmount = fmod(interpolateAmount + game->deltaTime, 1.0f);

        int splinePointSize = loopSpline ? splinePoints.size() : splinePoints.size() - 1;

        for (size_t i = 0; i < splinePointSize; i++)
        {
            int nextPoint = (i + 1) % splinePoints.size();

            Transform a = splinePoints[i]->transform;
            Transform b = splinePoints[nextPoint]->transform;

            glm::vec2 aOffset = splinePoints[i]->handles->get_handle_a_offset();
            glm::vec2 aHandle = a.position + aOffset;

            glm::vec2 bOffset = splinePoints[nextPoint]->handles->get_handle_b_offset();
            glm::vec2 bHandle = b.position + bOffset;

            glm::vec2 interpolatedPos = cubic_lerp(a.position, aHandle, bHandle, b.position, interpolateAmount);

            SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);

            DebugDraw::draw_debug_sphere(renderer,
                interpolatedPos - glm::vec2(game->camera->x, game->camera->y)
                , 10, 10);

            // draw curve
            int resolution = 10;
            glm::vec2 lastPointOnCurve = splinePoints[i]->transform.position;
            for (int i = 0; i < resolution; i++) {
                SDL_SetRenderDrawColor(renderer, 234, 239, 44, 255);
                float t = static_cast<float>(i) / static_cast<float>(resolution - 1);
                glm::vec2 newPoint = cubic_lerp(a.position, aHandle, bHandle, b.position, t);

                SDL_RenderDrawLineF(renderer,
                    lastPointOnCurve.x - game->camera->x,
                    lastPointOnCurve.y - game->camera->y,
                    newPoint.x - game->camera->x,
                    newPoint.y - game->camera->y);

                lastPointOnCurve = newPoint;
            }
        }
    }

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}

glm::vec2 Spline::quadratic_lerp(glm::vec2 a, glm::vec2 b, glm::vec2 c, float t) {
    glm::vec2 ab = glm::mix(a, b, t);
    glm::vec2 bc = glm::mix(b, c, t);

    return glm::mix(ab, bc, t);
}

glm::vec2 Spline::cubic_lerp(glm::vec2 a, glm::vec2 b, glm::vec2 c, glm::vec2 d, float t) {
    glm::vec2 ab_bc = quadratic_lerp(a, b, c, t);
    glm::vec2 bc_cd = quadratic_lerp(b, c, d, t);

    return glm::mix(ab_bc, bc_cd, t);
}