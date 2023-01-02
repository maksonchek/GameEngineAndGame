#pragma once

#include "GameObjectInterface.h"

#include <array>
#include <memory>

namespace RenderEngine {
    class Sprite;
}

class Eagle : public GameObjectInterface {
public:
    enum class EagleState {
        Alive = 0,
        Dead
    };

    Eagle(const glm::vec2& position, const glm::vec2& size, const float rotation, const float layer);
    virtual void Render() const override;
    void UpdateFrame(const double delta) override;

private:
    std::array<std::shared_ptr<RenderEngine::Sprite>, 2> sprite;
    EagleState currentState;
};