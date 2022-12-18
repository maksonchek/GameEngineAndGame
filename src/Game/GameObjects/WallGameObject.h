#pragma once

#include "GameObjectInterface.h"
#include <memory>

namespace RenderEngine {
    class Sprite;
}

class WallGameObject : public GameObjectInterface {
public:
    WallGameObject(const std::shared_ptr<RenderEngine::Sprite> pSprite, const glm::vec2& position, const glm::vec2& size, const float rotation);
    virtual void Render() const override;
    virtual void UpdateFrame(const uint64_t delta) override;

private:
    std::shared_ptr<RenderEngine::Sprite> pCurrentSprite;
};