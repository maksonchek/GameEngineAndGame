#include "Water.h"

#include "../../Resources/ResourceManager.h"
#include "../../Renderer/Sprite.h"

Water::Water(const glm::vec2& position, const glm::vec2& size, const float rotation, const float layer)
    : GameObjectInterface(GameObjectInterface::ObjectType::Constant_Satic_Object, position, size, rotation, layer)
    , sprite(ResourceManager::GetSprite("water"))
    , spriteAnimator(sprite)
    , blockOffsets{ glm::vec2(0, GOIsize.y / 2.f),
                       glm::vec2(GOIsize.x / 2.f, GOIsize.y / 2.f),
                       glm::vec2(0, 0),
                       glm::vec2(GOIsize.x / 2.f, 0) }
{
    boxColliders.emplace_back(glm::vec2(0), GOIsize);
}

void Water::RenderBlock(const BlockPosition blockLocation) const
{
    sprite->Render(GOIposition + blockOffsets[static_cast<size_t>(blockLocation)], GOIsize / 2.f, GOIrotation, GOIlayer, spriteAnimator.GetCurrentFrame());
}
 
void Water::Render() const
{
    RenderBlock(BlockPosition::TopLeft);
    RenderBlock(BlockPosition::TopRight);
    RenderBlock(BlockPosition::BottomLeft);
    RenderBlock(BlockPosition::BottomRight);
}

void Water::UpdateFrame(const double delta)
{
    spriteAnimator.Update(delta);
}

bool Water::IsCollides(const ObjectType objectType)
{
    return objectType != GameObjectInterface::ObjectType::Temporary_Dynamic_Object;
}
