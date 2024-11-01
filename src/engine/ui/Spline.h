#pragma once

#include <glm.hpp>
#include "../DebugDraw.h"

class Spline
{
public:
    Spline() {
        splinePoints.push_back(glm::vec2(100, 100));
    }
    ~Spline() {
        splinePoints.clear();
    }

    void render_debug(SDL_Renderer* renderer);

    void add_spline_point() {
        splinePoints.push_back(glm::vec2(100 * (splinePoints.size() + 1), 50 + 50 * (splinePoints.size() + 1)));
    }
    void remove_spline_point() {
        if(splinePoints.size() > 0)
        splinePoints.pop_back();
    }

	std::vector<glm::vec2> splinePoints;
};