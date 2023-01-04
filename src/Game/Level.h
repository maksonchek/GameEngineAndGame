#pragma once

#include <vector>
#include <string>
#include <memory>
#include <glm/vec2.hpp>

class GameObjectInterface;

class Level {
public:
    static constexpr unsigned int BLOCK_SIZE = 16;
    Level(const std::vector<std::string>& levelMarkup);
    void Render() const;
    void Update(const double delta);
    size_t GetLevelWidth() const;
    size_t GetLevelHeight() const;


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

    std::vector<std::shared_ptr<GameObjectInterface>> GetLevelObjects(const glm::vec2& bottomLeft, const glm::vec2& topRight) const;

private:
    size_t width = 0;
    size_t height = 0;
    unsigned int widthPixels = 0;
    unsigned int heightPixels = 0;
    glm::ivec2 playerRespawn1;
    glm::ivec2 playerRespawn2;
    glm::ivec2 enemyRespawn1;
    glm::ivec2 enemyRespawn2;
    glm::ivec2 enemyRespawn3;
    std::vector<std::shared_ptr<GameObjectInterface>> levelObjects;
};