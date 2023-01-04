#include "WallGameObject.h"
#include "../../Renderer/Sprite.h"
#include "../../Resources/ResourceManager.h"

WallGameObject::WallGameObject(const WallGOType type, const glm::vec2& position, const glm::vec2& size, const float rotation, const float layer)
    : GameObjectInterface(position, size, rotation, layer), currentWallGOState{ WallGOState::Destroyed, WallGOState::Destroyed, WallGOState::Destroyed, WallGOState::Destroyed }, 
                       offsets{ glm::vec2(0, GOIsize.y / 2.f),
                                   glm::vec2(GOIsize.x / 2.f, GOIsize.y / 2.f),
                                   glm::vec2(0, 0),
                                   glm::vec2(GOIsize.x / 2.f, 0) }
{
    pSprites[static_cast<size_t>(WallGOState::All)] = ResourceManager::GetSprite("brickWall_All");
    pSprites[static_cast<size_t>(WallGOState::TopLeft)] = ResourceManager::GetSprite("brickWall_TopLeft");
    pSprites[static_cast<size_t>(WallGOState::TopRight)] = ResourceManager::GetSprite("brickWall_TopRight");
    pSprites[static_cast<size_t>(WallGOState::Top)] = ResourceManager::GetSprite("brickWall_Top");
    pSprites[static_cast<size_t>(WallGOState::BottomLeft)] = ResourceManager::GetSprite("brickWall_BottomLeft");
    pSprites[static_cast<size_t>(WallGOState::Left)] = ResourceManager::GetSprite("brickWall_Left");
    pSprites[static_cast<size_t>(WallGOState::TopRight_BottomLeft)] = ResourceManager::GetSprite("brickWall_TopRight_BottomLeft");
    pSprites[static_cast<size_t>(WallGOState::Top_BottomLeft)] = ResourceManager::GetSprite("brickWall_Top_BottomLeft");
    pSprites[static_cast<size_t>(WallGOState::BottomRight)] = ResourceManager::GetSprite("brickWall_BottomRight");
    pSprites[static_cast<size_t>(WallGOState::TopLeft_BottomRight)] = ResourceManager::GetSprite("brickWall_TopLeft_BottomRight");
    pSprites[static_cast<size_t>(WallGOState::Right)] = ResourceManager::GetSprite("brickWall_Right");
    pSprites[static_cast<size_t>(WallGOState::Top_BottomRight)] = ResourceManager::GetSprite("brickWall_Top_BottomRight");
    pSprites[static_cast<size_t>(WallGOState::Bottom)] = ResourceManager::GetSprite("brickWall_Bottom");
    pSprites[static_cast<size_t>(WallGOState::TopLeft_Bottom)] = ResourceManager::GetSprite("brickWall_TopLeft_Bottom");
    pSprites[static_cast<size_t>(WallGOState::TopRight_Bottom)] = ResourceManager::GetSprite("brickWall_TopRight_Bottom");

    switch (type)
    {
    case WallGOType::All:
        currentWallGOState.fill(WallGOState::All);
        boxColliders.emplace_back(glm::vec2(0), GOIsize);
        break;
    case WallGOType::Top:
        currentWallGOState[static_cast<size_t>(WallGOPosition::TopLeft)] = WallGOState::All;
        currentWallGOState[static_cast<size_t>(WallGOPosition::TopRight)] = WallGOState::All;
        boxColliders.emplace_back(glm::vec2(0, GOIsize.y / 2), GOIsize);
        break;
    case WallGOType::Bottom:
        currentWallGOState[static_cast<size_t>(WallGOPosition::BottomLeft)] = WallGOState::All;
        currentWallGOState[static_cast<size_t>(WallGOPosition::BottomRight)] = WallGOState::All;
        boxColliders.emplace_back(glm::vec2(0), glm::vec2(GOIsize.x, GOIsize.y / 2));
        break;
    case WallGOType::Left:
        currentWallGOState[static_cast<size_t>(WallGOPosition::TopLeft)] = WallGOState::All;
        currentWallGOState[static_cast<size_t>(WallGOPosition::BottomLeft)] = WallGOState::All;
        boxColliders.emplace_back(glm::vec2(0), glm::vec2(GOIsize.x / 2, GOIsize.y)); 
        break;
    case WallGOType::Right:
        currentWallGOState[static_cast<size_t>(WallGOPosition::TopRight)] = WallGOState::All;
        currentWallGOState[static_cast<size_t>(WallGOPosition::BottomRight)] = WallGOState::All;
        boxColliders.emplace_back(glm::vec2(GOIsize.x / 2, 0), GOIsize);
        break;
    case WallGOType::TopLeft:
        currentWallGOState[static_cast<size_t>(WallGOPosition::TopLeft)] = WallGOState::All;
        boxColliders.emplace_back(glm::vec2(0, GOIsize.y / 2), glm::vec2(GOIsize.x / 2, GOIsize.y));
        break;
    case WallGOType::TopRight:
        currentWallGOState[static_cast<size_t>(WallGOPosition::TopRight)] = WallGOState::All;
        boxColliders.emplace_back(glm::vec2(GOIsize.x / 2, GOIsize.y / 2), GOIsize);
        break;
    case WallGOType::BottomLeft:
        currentWallGOState[static_cast<size_t>(WallGOPosition::BottomLeft)] = WallGOState::All;
        boxColliders.emplace_back(glm::vec2(0), glm::vec2(GOIsize.x / 2, GOIsize.y / 2));
        break;
    case WallGOType::BottomRight:
        currentWallGOState[static_cast<size_t>(WallGOPosition::BottomRight)] = WallGOState::All;
        boxColliders.emplace_back(glm::vec2(GOIsize.x / 2, 0), glm::vec2(GOIsize.x, GOIsize.y / 2));
        break;
    }
}
void WallGameObject::RenderWallGo(const WallGOPosition position) const
{
    const WallGOState state = currentWallGOState[static_cast<size_t>(position)];
    if (state != WallGOState::Destroyed)
    {
        pSprites[static_cast<size_t>(state)]->Render(GOIposition + offsets[static_cast<size_t>(position)], GOIsize / 2.f, GOIrotation, GOIlayer);
    }
}
void WallGameObject::Render() const
{
    RenderWallGo(WallGOPosition::TopLeft);
    RenderWallGo(WallGOPosition::TopRight);
    RenderWallGo(WallGOPosition::BottomLeft);
    RenderWallGo(WallGOPosition::BottomRight);
}

void WallGameObject::UpdateFrame(const double delta)
{
}