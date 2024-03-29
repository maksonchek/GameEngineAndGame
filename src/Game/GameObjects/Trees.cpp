#include "Trees.h"

#include "../../Resources/ResourceManager.h"
#include "../../Renderer/Sprite.h"

Trees::Trees(const glm::vec2& position, const glm::vec2& size, const float rotation, const float layer)
    : GameObjectInterface(GameObjectInterface::ObjectType::Constant_Satic_Object, position, size, rotation, layer)
    , sprite(ResourceManager::GetSprite("trees"))
    , blockOffsets{ glm::vec2(0, GOIsize.y / 2.f),
                       glm::vec2(GOIsize.x / 2.f, GOIsize.y / 2.f),
                       glm::vec2(0, 0),
                       glm::vec2(GOIsize.x / 2.f, 0) }
{
}

void Trees::RenderBlock(const BlockPosition blockLocation) const
{
    sprite->Render(GOIposition + blockOffsets[static_cast<size_t>(blockLocation)], GOIsize / 2.f, GOIrotation, GOIlayer);
}

void Trees::Render() const
{
    RenderBlock(BlockPosition::TopLeft);
    RenderBlock(BlockPosition::TopRight);
    RenderBlock(BlockPosition::BottomLeft);
    RenderBlock(BlockPosition::BottomRight);
}