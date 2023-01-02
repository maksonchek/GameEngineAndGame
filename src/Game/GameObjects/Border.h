#pragma once

#include "GameObjectInterface.h"

#include <array>
#include <memory>

namespace RenderEngine {
    class Sprite;
}

class Border : public GameObjectInterface {
public:

    Border(const glm::vec2& position, const glm::vec2& size, const float rotation, const float layer);
    virtual void Render() const override;

private:
    std::shared_ptr<RenderEngine::Sprite> sprite;
};