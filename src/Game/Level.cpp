#include "Level.h"

#include "../Resources/ResourceManager.h"
#include "GameObjects/GameObjectInterface.h"
#include "GameObjects/WallGameObject.h"
#include "GameObjects/ConcreteWallGameObject.h"

#include <iostream>

const unsigned int BLOCK_SIZE = 16;

std::shared_ptr<GameObjectInterface> CreateGameObjectFromMarkup(const char markup, const glm::vec2& position, const glm::vec2& size, const float rotation)
{
    switch (markup)
    {
    case '0':
        return std::make_shared<WallGameObject>(WallGameObject::WallGOType::Right, position, size, rotation);
    case '1':
        return std::make_shared<WallGameObject>(WallGameObject::WallGOType::Bottom, position, size, rotation);
    case '2':
        return std::make_shared<WallGameObject>(WallGameObject::WallGOType::Left, position, size, rotation);
    case '3':
        return std::make_shared<WallGameObject>(WallGameObject::WallGOType::Top, position, size, rotation);
    case '4':
        return std::make_shared<WallGameObject>(WallGameObject::WallGOType::All, position, size, rotation);
    case '5':
        return std::make_shared<ConcreteWallGameObject>(ConcreteWallGameObject::WallGOType::Right, position, size, rotation);
    case '6':
        return std::make_shared<ConcreteWallGameObject>(ConcreteWallGameObject::WallGOType::Bottom, position, size, rotation);
    case '7':
        return std::make_shared<ConcreteWallGameObject>(ConcreteWallGameObject::WallGOType::Left, position, size, rotation);
    case '8':
        return std::make_shared<ConcreteWallGameObject>(ConcreteWallGameObject::WallGOType::Top, position, size, rotation);
    case '9':
        return std::make_shared<ConcreteWallGameObject>(ConcreteWallGameObject::WallGOType::All, position, size, rotation);
    case 'G':
        return std::make_shared<WallGameObject>(WallGameObject::WallGOType::BottomLeft, position, size, rotation);
    case 'H':
        return std::make_shared<WallGameObject>(WallGameObject::WallGOType::BottomRight, position, size, rotation);
    case 'I':
        return std::make_shared<WallGameObject>(WallGameObject::WallGOType::TopLeft, position, size, rotation);
    case 'J':
        return std::make_shared<WallGameObject>(WallGameObject::WallGOType::TopRight, position, size, rotation);
    case 'D':
        return nullptr;
    default:
        std::cerr << "Unknown GameObject markup: " << markup << std::endl;
    }
    return nullptr;
}


Level::Level(const std::vector<std::string>& levelMarkup)
{
    if (levelMarkup.empty())
    {
        std::cerr << "Empty level markup!" << std::endl;
    }

    width = levelMarkup[0].length();
    height = levelMarkup.size();

    levelObjects.reserve(width * height);
    unsigned int currentBottomOffset = static_cast<unsigned int>(BLOCK_SIZE * (height - 1));
    for (const std::string& currentRow : levelMarkup)
    {
        unsigned int currentLeftOffset = 0;
        for (const char currentElement : currentRow)
        {
            levelObjects.emplace_back(CreateGameObjectFromMarkup(currentElement, glm::vec2(currentLeftOffset, currentBottomOffset), glm::vec2(BLOCK_SIZE, BLOCK_SIZE), 0.f));
            currentLeftOffset += BLOCK_SIZE;
        }
        currentBottomOffset -= BLOCK_SIZE;
    }
}

void Level::Render() const
{
    for (const auto& currentLevelObject : levelObjects)
    {
        if (currentLevelObject)
        {
            currentLevelObject->Render();
        }
    }
}

void Level::Update(const uint64_t delta)
{
    for (const auto& currentLevelObject : levelObjects)
    {
        if (currentLevelObject)
        {
            currentLevelObject->UpdateFrame(delta);
        }
    }
}