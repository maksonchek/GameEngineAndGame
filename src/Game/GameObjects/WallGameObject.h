#pragma once

#include "GameObjectInterface.h"
#include <memory>
#include <array>

namespace RenderEngine {
    class Sprite;
}

class WallGameObject : public GameObjectInterface {
public:
    enum class WallGOType {
        All,
        Top,
        Bottom,
        Left,
        Right,
        TopLeft,
        TopRight,
        BottomLeft,
        BottomRight
    };

    enum class WallGOState {
        All = 0,
        TopLeft,
        TopRight,
        Top,
        BottomLeft,
        Left,
        TopRight_BottomLeft,
        Top_BottomLeft,
        BottomRight,
        TopLeft_BottomRight,
        Right,
        Top_BottomRight,
        Bottom,
        TopLeft_Bottom,
        TopRight_Bottom,
        Destroyed
    };

    enum class WallGOPosition {
        TopLeft,
        TopRight,
        BottomLeft,
        BottomRight
    };

    WallGameObject(const WallGOType type, const glm::vec2& position, const glm::vec2& size, const float rotation);
    virtual void Render() const override;
    virtual void UpdateFrame(const uint64_t delta) override;

private:
    void RenderWallGo(const WallGOPosition position) const;

    std::array<WallGOState, 4> currentWallGOState;
    std::array<std::shared_ptr<RenderEngine::Sprite>, 15> pSprites;
};