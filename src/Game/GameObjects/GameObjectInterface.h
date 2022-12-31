#pragma once 

#include <glm/vec2.hpp>

class GameObjectInterface {
public:
    GameObjectInterface(const glm::vec2& position, const glm::vec2& size, const float rotation);
    virtual void Render() const = 0;
    virtual void UpdateFrame(const uint64_t delta) = 0;
    virtual ~GameObjectInterface();

protected:
    glm::vec2 GOIposition;
    glm::vec2 GOIsize;
    float GOIrotation;
};