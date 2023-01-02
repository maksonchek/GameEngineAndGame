#pragma once

#include "GameObjectInterface.h"
#include <memory>
#include <array>

namespace RenderEngine {
    class Sprite;
}

class ConcreteWallGameObject : public GameObjectInterface {
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
        Enabled = 0,
        Destroyed
    };

    enum class WallGOPosition {
        TopLeft,
        TopRight,
        BottomLeft,
        BottomRight
    };

    ConcreteWallGameObject(const WallGOType type, const glm::vec2& position, const glm::vec2& size, const float rotation, const float layer);
    virtual void Render() const override;
    virtual void UpdateFrame(const double delta) override;

private:
    void RenderWallGo(const WallGOPosition position) const;

    std::array<WallGOState, 4> currentWallGOState;
    std::shared_ptr<RenderEngine::Sprite> sprite;
    std::array<glm::vec2, 4> offsets;
};