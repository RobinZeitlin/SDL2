#pragma once

#include <glm.hpp>
#include <SDL.h>

namespace DebugDraw
{
    /**
     * @brief A debug draw library using SDL inspired by Unreal Engine 5, by Robin Zeitlin.
     */

    inline void draw_debug_sphere(SDL_Renderer* renderer, glm::vec2 position, float radius, int numSegments) {
		const float increment = 2.0f * M_PI / numSegments;
		std::vector<SDL_FPoint> points;
		float angle = 0.0f;

		for (int i = 0; i < numSegments; i++) {
			float x = (position.x + radius * glm::cos(angle));
			float y = (position.y + radius * glm::sin(angle));

			SDL_FPoint newPos = { x, y };
			points.push_back(newPos);

			angle += increment;
		}

		points.push_back(points[0]);

		SDL_RenderDrawLinesF(renderer, points.data(), numSegments + 1);
    }
}