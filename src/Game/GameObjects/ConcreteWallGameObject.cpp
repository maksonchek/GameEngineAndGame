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

    //В конструкторе передаём значения в GameObjectInterface. Во первых, нужно указать тип объекта. Всего их 4. Constant_Satic_Object, Constant_Dynamic_Object, 
    //Temporary_Satic_Object, Temporary_Dynamic_Object. 
    //Подвижный, способный к взаимодействию объект, подвижный неспособный к взаимодействию объект, неподвижный, способный к взаимодействию объект, непоодвижный неспособный к взаимодействию объект. В данном случае это Constant_Satic_Object
    //Далее передаём позицию, размер, поворот и слой отрисовки, как и в базовом конструкторе.
    //Инициализация sprite - ResourceManager::GetSprite("betonWall"), где betonWall - имя текстуры и спрайта, размеченного в json файле
    //Инициализация offsets - расписываем смещения для каждого типа текстуры. Переменные c надписью GOI - переменные GameObjectInterface, которыми нужно пользоваться
{

    switch (type) //Далее в конструкторе типа стены, который создаём присваиваем состояние Enabled. Сообщаем физическому движку, что объект твёрдый (накидываем коллайдер на него) с помощью  boxColliders.emplace_back(glm::vec2(0), GOIsize);
    {
    case WallGOType::All:
        currentWallGOState.fill(WallGOState::Enabled);
        boxColliders.emplace_back(glm::vec2(0), GOIsize);
        break;
    case WallGOType::Top:
        currentWallGOState[static_cast<size_t>(WallGOPosition::TopLeft)] = WallGOState::Enabled;
        currentWallGOState[static_cast<size_t>(WallGOPosition::TopRight)] = WallGOState::Enabled;
        boxColliders.emplace_back(glm::vec2(0, GOIsize.y/2), GOIsize); //Для каждого коллайдера указываем свои координаты и размер
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
    const WallGOState state = currentWallGOState[static_cast<size_t>(position)]; //получаем состояние объекта
    if (state != WallGOState::Destroyed) //если он активен, отрисовываем на уровне, передвая позицию со смещением, размеры, поворот и слой отрисовки
    {
        sprite->Render(GOIposition + offsets[static_cast<size_t>(position)], GOIsize / 2.f, GOIrotation, GOIlayer); //Здесь идёт отрисовка участка стены 8*8, поэтому нужно смещение, которое задаётся позицией.
    } 
    //Отрисовка 8 на 8 нужна, чтобы в случае отрисовки половины стены можно было не рисовать её половину
}
void ConcreteWallGameObject::Render() const
{
    RenderWallGo(WallGOPosition::TopLeft); //Отрисовываем каждый участок стены 8*8
    RenderWallGo(WallGOPosition::TopRight);
    RenderWallGo(WallGOPosition::BottomLeft);
    RenderWallGo(WallGOPosition::BottomRight);
}

void ConcreteWallGameObject::UpdateFrame(const double delta)
{
    //С этой стеной ничто не может произойти. Она статична на уровне, поэтому она постоянная каждый кадр
}