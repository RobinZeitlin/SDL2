#pragma once

#include <glm.hpp>
#include "../DebugDraw.h"

#include "SplinePoint.h"

class Spline
{
public:
    ~Spline() {
        for (auto point : splinePoints)
            delete point;

        clear_spline_points();
        splinePoints.clear();
    }

    void render_debug(SDL_Renderer* renderer);

    void add_spline_point() {
        auto newPoint = new SplinePoint();
        newPoint->transform.position = glm::vec2(100 * (splinePoints.size() + 1), 50 + 50 * (splinePoints.size() + 1));

        splinePoints.push_back(newPoint);
    }
    void remove_spline_point() {
        if (splinePoints.size() > 0) {
            delete splinePoints.back();     
            splinePoints.pop_back();
        }
    }

    void clear_spline_points() {
        for (auto& point : splinePoints) {
            delete point;
        }
    }

    glm::vec2 quadratic_lerp(glm::vec2 a, glm::vec2 b, glm::vec2 c, float t);
    glm::vec2 cubic_lerp(glm::vec2 a, glm::vec2 b, glm::vec2 c, glm::vec2 d, float t);

	std::vector<SplinePoint*> splinePoints;

    float interpolateAmount;

    bool loopSpline;
};