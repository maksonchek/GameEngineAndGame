#include "Ice.h"

#include "../../Resources/ResourceManager.h"
#include "../../Renderer/Sprite.h"

Ice::Ice(const glm::vec2& position, const glm::vec2& size, const float rotation, const float layer)
    : GameObjectInterface(position, size, rotation, layer)
    , sprite(ResourceManager::GetSprite("ice"))
    , blockOffsets{ glm::vec2(0, GOIsize.y / 2.f),
                       glm::vec2(GOIsize.x / 2.f, GOIsize.y / 2.f),
                       glm::vec2(0, 0),
                       glm::vec2(GOIsize.x / 2.f, 0) }
{
}

void Ice::RenderBlock(const BlockPosition blockLocation) const
{
    sprite->Render(GOIposition + blockOffsets[static_cast<size_t>(blockLocation)], GOIsize / 2.f, GOIrotation, GOIlayer);
}

void Ice::Render() const
{
    RenderBlock(BlockPosition::TopLeft);
    RenderBlock(BlockPosition::TopRight);
    RenderBlock(BlockPosition::BottomLeft);
    RenderBlock(BlockPosition::BottomRight);
}