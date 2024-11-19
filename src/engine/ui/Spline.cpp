#include "Spline.h"

#include <cmath>
#include "../zmath.h"

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

            glm::vec2 interpolatedPos = zmath::cubic_lerp(a.position, aHandle, bHandle, b.position, interpolateAmount);


            int resolution = 10;
            glm::vec2 lastPointOnCurve = splinePoints[i]->transform.position;
            for (size_t j = 0; j < resolution; j++) {
                SDL_SetRenderDrawColor(renderer, 234, 239, 44, 255);
                float t = static_cast<float>(j) / static_cast<float>(resolution - 1);
                glm::vec2 newPoint = zmath::cubic_lerp(a.position, aHandle, bHandle, b.position, t);

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

glm::vec2 Spline::get_global_position(float globalProgress)
{
    globalProgress = glm::clamp(globalProgress, 0.0f, 1.0f);

    float totalLength = 0.0f;
    std::vector<float> segmentLengths;

    int splinePointSize = loopSpline ? splinePoints.size() : splinePoints.size() - 1;

    for (size_t i = 0; i < splinePointSize; i++) {
        int nextPoint = (i + 1) % splinePoints.size();

        glm::vec2 a = splinePoints[i]->transform.position;
        glm::vec2 b = splinePoints[nextPoint]->transform.position;

        glm::vec2 aOffset = splinePoints[i]->handles->get_handle_a_offset();
        glm::vec2 aHandle = a + aOffset;

        glm::vec2 bOffset = splinePoints[nextPoint]->handles->get_handle_b_offset();
        glm::vec2 bHandle = b + bOffset;

        float segmentLength = 0.0f;
        glm::vec2 lastPoint = a;
        int resolution = 10;

        for (size_t j = 1; j <= resolution; j++) {
            float t = static_cast<float>(j) / resolution;
            glm::vec2 point = zmath::cubic_lerp(a, aHandle, bHandle, b, t);

            segmentLength += glm::distance(lastPoint, point);
            lastPoint = point;
        }

        segmentLengths.push_back(segmentLength);
        totalLength += segmentLength;
    }

    float targetLength = globalProgress * totalLength;
    float accumulatedLength = 0.0f;

    for (size_t i = 0; i < splinePointSize; i++) {
        if (accumulatedLength + segmentLengths[i] >= targetLength) {

            float segmentProgress = (targetLength - accumulatedLength) / segmentLengths[i];
            int nextPoint = (i + 1) % splinePoints.size();

            glm::vec2 a = splinePoints[i]->transform.position;
            glm::vec2 b = splinePoints[nextPoint]->transform.position;

            glm::vec2 aOffset = splinePoints[i]->handles->get_handle_a_offset();
            glm::vec2 aHandle = a + aOffset;

            glm::vec2 bOffset = splinePoints[nextPoint]->handles->get_handle_b_offset();
            glm::vec2 bHandle = b + bOffset;

            return zmath::cubic_lerp(a, aHandle, bHandle, b, segmentProgress);
        }

        accumulatedLength += segmentLengths[i];
    }
    return splinePoints.back()->transform.position;
}

glm::vec2 Spline::get_closest_point_on_spline(glm::vec2 comparisonPos) {
    const int resolution = 100;

    float closestDistance = std::numeric_limits<float>::max();

    glm::vec2 closestPoint;
    glm::vec2 points[resolution];

    for (size_t i = 0; i < resolution; i++) {
        float splineProgress = static_cast<float>(i) / (resolution - 1);

        glm::vec2 positionOnSpline = get_global_position(splineProgress);

        float dist = zmath::get_distance(positionOnSpline, comparisonPos);
        if (dist < closestDistance) {
            closestDistance = dist;
            closestPoint = positionOnSpline;
        }
    }

    return closestPoint;
}