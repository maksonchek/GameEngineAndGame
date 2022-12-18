#include "WallGameObject.h"
#include "../../Renderer/Sprite.h"

WallGameObject::WallGameObject(const std::shared_ptr<RenderEngine::Sprite> pSprite, const glm::vec2& position, const glm::vec2& size, const float rotation) : GameObjectInterface(position, size, rotation), pCurrentSprite(std::move(pSprite))
{
}
void WallGameObject::Render() const
{
    pCurrentSprite->Render(position, size, rotation);
}

void WallGameObject::UpdateFrame(const uint64_t delta)
{
}