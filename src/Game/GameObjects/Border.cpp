#include "Border.h"

#include "../../Resources/ResourceManager.h"
#include "../../Renderer/Sprite.h"

Border::Border(const glm::vec2& position, const glm::vec2& size, const float rotation, const float layer) : GameObjectInterface(position, size, rotation, layer), sprite(ResourceManager::GetSprite("borderWall"))
{
    boxColliders.emplace_back(glm::vec2(0), GOIsize);
}

void Border::Render() const
{
    sprite->Render(GOIposition, GOIsize, GOIrotation, GOIlayer);
}