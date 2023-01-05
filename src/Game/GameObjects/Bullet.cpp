#include "Bullet.h"

#include "../../Resources/ResourceManager.h"
#include "../../Renderer/Sprite.h"

Bullet::Bullet(const double velocity, const glm::vec2& position, const glm::vec2& size, const float layer) : GameObjectInterface(GameObjectInterface::ObjectType::Temporary_Dynamic_Object, position, size, 0.f, layer)
                                                                                                                                        , pSprite_top(ResourceManager::GetSprite("bullet_Top"))
                                                                                                                                        , pSprite_bottom(ResourceManager::GetSprite("bullet_Bottom"))
                                                                                                                                        , pSprite_left(ResourceManager::GetSprite("bullet_Left"))
                                                                                                                                        , pSprite_right(ResourceManager::GetSprite("bullet_Right"))
                                                                                                                                        , objectOrientation(ObjectOrientation::Top)
                                                                                                                                        , maxVelocity(velocity)
                                                                                                                                        , isActive(false)
{
    boxColliders.emplace_back(glm::vec2(0), size);
}

void Bullet::Render() const
{
    if (isActive) {
        switch (objectOrientation)
        {
        case ObjectOrientation::Top:
            pSprite_top->Render(GOIposition, GOIsize, GOIrotation, GOIlayer);
            break;
        case ObjectOrientation::Bottom:
            pSprite_bottom->Render(GOIposition, GOIsize, GOIrotation, GOIlayer);
            break;
        case ObjectOrientation::Left:
            pSprite_left->Render(GOIposition, GOIsize, GOIrotation, GOIlayer);
            break;
        case ObjectOrientation::Right:
            pSprite_right->Render(GOIposition, GOIsize, GOIrotation, GOIlayer);
            break;
        }
    }
}

void Bullet::Fire(const glm::vec2& position, const glm::vec2& direction)
{
    GOIposition = position;
    GOIdirection = direction;
    if (GOIdirection.x == 0.f)
    {
        objectOrientation = (GOIdirection.y < 0) ? ObjectOrientation::Bottom : ObjectOrientation::Top;
    }
    else
    {
        objectOrientation = (GOIdirection.x < 0) ? ObjectOrientation::Left : ObjectOrientation::Right;
    }
    isActive = true;
    SetVelocity(maxVelocity);
}
void Bullet::OnCollision()
{
    SetVelocity(0);
    isActive = false;
}