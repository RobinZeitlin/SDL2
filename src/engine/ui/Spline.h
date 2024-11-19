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

    glm::vec2 get_global_position(float globalProgress);
    glm::vec2 get_closest_point_on_spline(glm::vec2 comparisonPos);

	std::vector<SplinePoint*> splinePoints;

    float interpolateAmount;

    bool loopSpline;
};