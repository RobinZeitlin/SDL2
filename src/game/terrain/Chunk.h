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
                auto newBlock = new Block();
                game->spawnActor<Block>(newBlock, glm::vec2(x, y));
                blockData[{x, y}] = newBlock;
                blockData[{x, y}]->transform.position = { x, y };
            }
        }
    }

    Block* get_block(glm::vec2 blockPos)
    {
        return blockData[blockPos];
    }

    glm::vec2 chunkSize = { 1, 2 };
    std::unordered_map<glm::vec2, Block*, Vec2Hash> blockData;
};
