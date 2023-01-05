#pragma once

#include "GameObjectInterface.h"

#include <array>
#include <memory>

namespace RenderEngine {
    class Sprite;
}

class Bullet : public GameObjectInterface {
public:
    enum class ObjectOrientation : uint8_t {
        Top,
        Bottom,
        Left,
        Right
    };

    Bullet(const double velocity, const glm::vec2& position, const glm::vec2& size, const float layer);
    virtual void Render() const override;
    bool IsActive() const { return isActive; }
    void Fire(const glm::vec2& position, const glm::vec2& direction);
    virtual void OnCollision() override;

private:
    std::shared_ptr<RenderEngine::Sprite> pSprite_top;
    std::shared_ptr<RenderEngine::Sprite> pSprite_bottom;
    std::shared_ptr<RenderEngine::Sprite> pSprite_left;
    std::shared_ptr<RenderEngine::Sprite> pSprite_right;
    ObjectOrientation objectOrientation;
    double maxVelocity;
    bool isActive;
};