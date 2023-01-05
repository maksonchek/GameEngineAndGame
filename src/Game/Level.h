#pragma once

#include <vector>
#include <string>
#include <memory>
#include <glm/vec2.hpp>
#include "LevelInterface.h"


class Level : public LevelInterface 
{
public:

    Level(const std::vector<std::string>& levelMarkup);

    const glm::ivec2& GetPlayerRespawn_1() const 
    { 
        return playerRespawn1; 
    }

    const glm::ivec2& GetPlayerRespawn_2() const 
    { 
        return playerRespawn2; 
    }

    const glm::ivec2& GetEnemyRespawn_1() const 
    { 
        return enemyRespawn1; 
    }

    const glm::ivec2& GetEnemyRespawn_2() const 
    { 
        return enemyRespawn2; 
    }

    const glm::ivec2& GetEnemyRespawn_3() const 
    { 
        return enemyRespawn3; 
    }


private:
    glm::ivec2 playerRespawn1;
    glm::ivec2 playerRespawn2;
    glm::ivec2 enemyRespawn1;
    glm::ivec2 enemyRespawn2;
    glm::ivec2 enemyRespawn3;
};