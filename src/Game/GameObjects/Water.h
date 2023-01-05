#pragma once

#include "GameObjectInterface.h"
#include "../../Renderer/SpriteAnimator.h"

#include <array>
#include <memory>

namespace RenderEngine {
    class Sprite;
}

class Water : public GameObjectInterface {
public:

    enum class BlockPosition{
        TopLeft,
        TopRight,
        BottomLeft,
        BottomRight
    };

    Water(const glm::vec2& position, const glm::vec2& size, const float rotation, const float layer);
    virtual void Render() const override;

    void UpdateFrame(const double delta) override;

    virtual bool IsCollides(const ObjectType objectType) override;

private:
    void RenderBlock(const BlockPosition blockLocation) const;

    std::shared_ptr<RenderEngine::Sprite> sprite;
    RenderEngine::SpriteAnimator spriteAnimator;
    std::array<glm::vec2, 4> blockOffsets;
};