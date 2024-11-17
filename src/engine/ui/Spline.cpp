#include "Spline.h"

#include <cmath>

#include "../../Game.h"
#include "../DebugDraw.h"

void Spline::render_debug(SDL_Renderer* renderer)
{
    glm::vec2 lastPoint = glm::vec2(0);

    for (auto point : splinePoints) {
        point->render_point();

        SDL_SetRenderDrawColor(renderer, 234, 239, 44, 255);

        if (lastPoint != glm::vec2(0)) {
            SDL_RenderDrawLineF(renderer,
                lastPoint.x - game->camera->x,
                lastPoint.y - game->camera->y,
                point->transform.position.x - game->camera->x,
                point->transform.position.y - game->camera->y);
        }

        lastPoint = point->transform.position;
    }

    if (splinePoints.size() > 1) {
        interpolateAmount = fmod(interpolateAmount + game->deltaTime, 1.0f);

        Transform a = splinePoints[0]->transform;
        Transform b = splinePoints[1]->transform;

        glm::vec2 aOffset = a.get_transform_up() * 80.0f;
        glm::vec2 aHandle = a.position + aOffset;

        glm::vec2 bOffset = b.get_transform_up() * 80.0f;
        glm::vec2 bHandle = b.position + bOffset;
        
        glm::vec2 interpolatedPos = cubic_lerp(a.position, aHandle, bHandle, b.position, interpolateAmount);
            
        DebugDraw::draw_debug_sphere(renderer, 
            interpolatedPos - glm::vec2(game->camera->x, game->camera->y)
            , 10, 10);

        // draw curve
        int resolution = 10;
        glm::vec2 lastPointOnCurve = splinePoints[0]->transform.position;
        for (int i = 0; i < resolution; i++) {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
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