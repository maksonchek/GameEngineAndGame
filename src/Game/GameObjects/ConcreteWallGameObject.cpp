#include "ConcreteWallGameObject.h"
#include "../../Renderer/Sprite.h"
#include "../../Resources/ResourceManager.h"

ConcreteWallGameObject::ConcreteWallGameObject(const WallGOType type, const glm::vec2& position, const glm::vec2& size, const float rotation)
    : GameObjectInterface(position, size, rotation), currentWallGOState{ WallGOState::Destroyed, WallGOState::Destroyed, WallGOState::Destroyed, WallGOState::Destroyed }, 
            sprite(ResourceManager::GetSprite("betonWall")),                        
                                    offsets{ glm::vec2(0, GOIsize.y / 2.f),
                                   glm::vec2(GOIsize.x / 2.f, GOIsize.y / 2.f),
                                   glm::vec2(0, 0),
                                   glm::vec2(GOIsize.x / 2.f, 0) }
{

    switch (type)
    {
    case WallGOType::All:
        currentWallGOState.fill(WallGOState::Enabled);
        break;
    case WallGOType::Top:
        currentWallGOState[static_cast<size_t>(WallGOPosition::TopLeft)] = WallGOState::Enabled;
        currentWallGOState[static_cast<size_t>(WallGOPosition::TopRight)] = WallGOState::Enabled;
        break;
    case WallGOType::Bottom:
        currentWallGOState[static_cast<size_t>(WallGOPosition::BottomLeft)] = WallGOState::Enabled;
        currentWallGOState[static_cast<size_t>(WallGOPosition::BottomRight)] = WallGOState::Enabled;
        break;
    case WallGOType::Left:
        currentWallGOState[static_cast<size_t>(WallGOPosition::TopLeft)] = WallGOState::Enabled;
        currentWallGOState[static_cast<size_t>(WallGOPosition::BottomLeft)] = WallGOState::Enabled;
        break;
    case WallGOType::Right:
        currentWallGOState[static_cast<size_t>(WallGOPosition::TopRight)] = WallGOState::Enabled;
        currentWallGOState[static_cast<size_t>(WallGOPosition::BottomRight)] = WallGOState::Enabled;
        break;
    case WallGOType::TopLeft:
        currentWallGOState[static_cast<size_t>(WallGOPosition::TopLeft)] = WallGOState::Enabled;
        break;
    case WallGOType::TopRight:
        currentWallGOState[static_cast<size_t>(WallGOPosition::TopRight)] = WallGOState::Enabled;
        break;
    case WallGOType::BottomLeft:
        currentWallGOState[static_cast<size_t>(WallGOPosition::BottomLeft)] = WallGOState::Enabled;
        break;
    case WallGOType::BottomRight:
        currentWallGOState[static_cast<size_t>(WallGOPosition::BottomRight)] = WallGOState::Enabled;
        break;
    }
}
void ConcreteWallGameObject::RenderWallGo(const WallGOPosition position) const
{
    const WallGOState state = currentWallGOState[static_cast<size_t>(position)];
    if (state != WallGOState::Destroyed)
    {
        sprite->Render(GOIposition + offsets[static_cast<size_t>(position)], GOIsize / 2.f, GOIrotation);
    }
}
void ConcreteWallGameObject::Render() const
{
    RenderWallGo(WallGOPosition::TopLeft);
    RenderWallGo(WallGOPosition::TopRight);
    RenderWallGo(WallGOPosition::BottomLeft);
    RenderWallGo(WallGOPosition::BottomRight);
}

void ConcreteWallGameObject::UpdateFrame(const uint64_t delta)
{
}