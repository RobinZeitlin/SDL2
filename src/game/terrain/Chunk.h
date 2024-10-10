#pragma once

#include <unordered_map>
#include <glm.hpp>
#include <SDL.h>

#include "Block.h"
#include "GrassBlock.h"
#include "../../Game.h"

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
                if (y == 0)
                {
                    auto newBlock = new GrassBlock();
                    game->spawnActor<GrassBlock>(newBlock, glm::vec2(x * 32, y * 32));
                    blockData[{x, y}] = newBlock;
                }
                else
                {
                    auto newBlock = new Block();
                    game->spawnActor<Block>(newBlock, glm::vec2(x * 32, y * 32));
                    blockData[{x, y}] = newBlock;
                }
            }
        }
    }

    Block* get_block(glm::vec2 blockPos)
    {
        return blockData[blockPos];
    }

    glm::vec2 chunkSize = { 100, 5 };
    std::unordered_map<glm::vec2, Block*, Vec2Hash> blockData;
};
