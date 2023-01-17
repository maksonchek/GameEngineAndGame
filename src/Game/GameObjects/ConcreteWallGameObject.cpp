#include "ConcreteWallGameObject.h"
#include "../../Renderer/Sprite.h"
#include "../../Resources/ResourceManager.h"

ConcreteWallGameObject::ConcreteWallGameObject(const WallGOType type, const glm::vec2& position, const glm::vec2& size, const float rotation, const float layer)
    : GameObjectInterface(GameObjectInterface::ObjectType::Constant_Satic_Object, position, size, rotation, layer), currentWallGOState{ WallGOState::Destroyed, WallGOState::Destroyed, WallGOState::Destroyed, WallGOState::Destroyed },
            sprite(ResourceManager::GetSprite("betonWall")),                        
                                   offsets{ glm::vec2(0, GOIsize.y / 2.f),
                                   glm::vec2(GOIsize.x / 2.f, GOIsize.y / 2.f),
                                   glm::vec2(0, 0),
                                   glm::vec2(GOIsize.x / 2.f, 0) }

    //� ������������ ������� �������� � GameObjectInterface. �� ������, ����� ������� ��� �������. ����� �� 4. Constant_Satic_Object, Constant_Dynamic_Object, 
    //Temporary_Satic_Object, Temporary_Dynamic_Object. 
    //���������, ��������� � �������������� ������, ��������� ����������� � �������������� ������, �����������, ��������� � �������������� ������, ������������ ����������� � �������������� ������. � ������ ������ ��� Constant_Satic_Object
    //����� ������� �������, ������, ������� � ���� ���������, ��� � � ������� ������������.
    //������������� sprite - ResourceManager::GetSprite("betonWall"), ��� betonWall - ��� �������� � �������, ������������ � json �����
    //������������� offsets - ����������� �������� ��� ������� ���� ��������. ���������� c �������� GOI - ���������� GameObjectInterface, �������� ����� ������������
{

    switch (type) //����� � ������������ ���� �����, ������� ������ ����������� ��������� Enabled. �������� ����������� ������, ��� ������ ������ (���������� ��������� �� ����) � �������  boxColliders.emplace_back(glm::vec2(0), GOIsize);
    {
    case WallGOType::All:
        currentWallGOState.fill(WallGOState::Enabled);
        boxColliders.emplace_back(glm::vec2(0), GOIsize);
        break;
    case WallGOType::Top:
        currentWallGOState[static_cast<size_t>(WallGOPosition::TopLeft)] = WallGOState::Enabled;
        currentWallGOState[static_cast<size_t>(WallGOPosition::TopRight)] = WallGOState::Enabled;
        boxColliders.emplace_back(glm::vec2(0, GOIsize.y/2), GOIsize); //��� ������� ���������� ��������� ���� ���������� � ������
        break;
    case WallGOType::Bottom:
        currentWallGOState[static_cast<size_t>(WallGOPosition::BottomLeft)] = WallGOState::Enabled;
        currentWallGOState[static_cast<size_t>(WallGOPosition::BottomRight)] = WallGOState::Enabled;
        boxColliders.emplace_back(glm::vec2(0), glm::vec2(GOIsize.x, GOIsize.y / 2));
        break;
    case WallGOType::Left:
        currentWallGOState[static_cast<size_t>(WallGOPosition::TopLeft)] = WallGOState::Enabled;
        currentWallGOState[static_cast<size_t>(WallGOPosition::BottomLeft)] = WallGOState::Enabled;
        boxColliders.emplace_back(glm::vec2(0), glm::vec2(GOIsize.x / 2, GOIsize.y));
        break;
    case WallGOType::Right:
        currentWallGOState[static_cast<size_t>(WallGOPosition::TopRight)] = WallGOState::Enabled;
        currentWallGOState[static_cast<size_t>(WallGOPosition::BottomRight)] = WallGOState::Enabled;
        boxColliders.emplace_back(glm::vec2(GOIsize.x / 2, 0), GOIsize);
        break;
    case WallGOType::TopLeft:
        currentWallGOState[static_cast<size_t>(WallGOPosition::TopLeft)] = WallGOState::Enabled;
        boxColliders.emplace_back(glm::vec2(0, GOIsize.y / 2), glm::vec2(GOIsize.x / 2, GOIsize.y));
        break;
    case WallGOType::TopRight:
        currentWallGOState[static_cast<size_t>(WallGOPosition::TopRight)] = WallGOState::Enabled;
        boxColliders.emplace_back(glm::vec2(GOIsize.x / 2, GOIsize.y / 2), GOIsize);
        break;
    case WallGOType::BottomLeft:
        currentWallGOState[static_cast<size_t>(WallGOPosition::BottomLeft)] = WallGOState::Enabled;
        boxColliders.emplace_back(glm::vec2(0), glm::vec2(GOIsize.x / 2, GOIsize.y / 2));
        break;
    case WallGOType::BottomRight:
        currentWallGOState[static_cast<size_t>(WallGOPosition::BottomRight)] = WallGOState::Enabled;
        boxColliders.emplace_back(glm::vec2(GOIsize.x / 2, 0), glm::vec2(GOIsize.x, GOIsize.y / 2));
        break;
    }
}
void ConcreteWallGameObject::RenderWallGo(const WallGOPosition position) const 
{
    const WallGOState state = currentWallGOState[static_cast<size_t>(position)]; //�������� ��������� �������
    if (state != WallGOState::Destroyed) //���� �� �������, ������������ �� ������, �������� ������� �� ���������, �������, ������� � ���� ���������
    {
        sprite->Render(GOIposition + offsets[static_cast<size_t>(position)], GOIsize / 2.f, GOIrotation, GOIlayer); //����� ��� ��������� ������� ����� 8*8, ������� ����� ��������, ������� ������� ��������.
    } 
    //��������� 8 �� 8 �����, ����� � ������ ��������� �������� ����� ����� ���� �� �������� � ��������
}
void ConcreteWallGameObject::Render() const
{
    RenderWallGo(WallGOPosition::TopLeft); //������������ ������ ������� ����� 8*8
    RenderWallGo(WallGOPosition::TopRight);
    RenderWallGo(WallGOPosition::BottomLeft);
    RenderWallGo(WallGOPosition::BottomRight);
}

void ConcreteWallGameObject::UpdateFrame(const double delta)
{
    //� ���� ������ ����� �� ����� ���������. ��� �������� �� ������, ������� ��� ���������� ������ ����
}