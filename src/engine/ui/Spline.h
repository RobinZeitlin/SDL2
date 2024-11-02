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

        splinePoints.clear();
    }

    void render_debug(SDL_Renderer* renderer);

    void add_spline_point() {
        auto newPoint = new SplinePoint();
        newPoint->pos = glm::vec2(100 * (splinePoints.size() + 1), 50 + 50 * (splinePoints.size() + 1));

        splinePoints.push_back(newPoint);
    }
    void remove_spline_point() {
        if (splinePoints.size() > 0) {
            delete splinePoints.back();     
            splinePoints.pop_back();
        }
    }

	std::vector<SplinePoint*> splinePoints;
};