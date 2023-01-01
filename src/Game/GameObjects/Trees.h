#pragma once

#include "GameObjectInterface.h"

#include <array>
#include <memory>

namespace RenderEngine {
    class Sprite;
}

class Trees : public GameObjectInterface {
public:

    enum class BlockPosition : uint8_t {
        TopLeft,
        TopRight,
        BottomLeft,
        BottomRight
    };

    Trees(const glm::vec2& position, const glm::vec2& size, const float rotation, const float layer);
    virtual void Render() const override;

private:
    void RenderBlock(const BlockPosition blockLocation) const;

    std::shared_ptr<RenderEngine::Sprite> sprite;
    std::array<glm::vec2, 4> blockOffsets;
};