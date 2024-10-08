#pragma once

#include <unordered_map>
#include <glm.hpp>
#include <SDL.h>

#include "Block.h"

struct Vec2Hash {
    std::size_t operator()(const glm::vec2& v) const {
        return std::hash<float>()(v.x) ^ std::hash<float>()(v.y);
    }
};

class Chunk
{
public:
    Chunk() {};
    ~Chunk() {
        blockData.clear();
    };

    void Init()
    {
        for (int x = 0; x < chunkSize.x; x++)
        {
            for (int y = 0; y < chunkSize.y; y++)
            {
                blockData[{x, y}] = new Block();
                blockData[{x, y}]->transform.position = { x, y };
            }
        }
    }

    void RenderChunk(SDL_Renderer* renderer, Player* player, Camera* camera)
    {
        for (auto& [position, block] : blockData)
        {
            if (block)
            {
                float distanceSquared = (position.x * 32 - player->transform.position.x) * (position.x * 32 - player->transform.position.x) +
                    (position.y * 32 - player->transform.position.y) * (position.y * 32 - player->transform.position.y);
                if (distanceSquared < 200 * 200) {
                    block->render(renderer, camera);
                }
            }
        }
    }

    glm::vec2 chunkSize = { 1, 2 };
    std::unordered_map<glm::vec2, Block*, Vec2Hash> blockData;
};
