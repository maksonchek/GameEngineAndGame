#include "Level.h"

#include "../Resources/ResourceManager.h"
#include "GameObjects/GameObjectInterface.h"
#include "GameObjects/WallGameObject.h"
#include "GameObjects/ConcreteWallGameObject.h"
#include "GameObjects/Trees.h"
#include "GameObjects/Ice.h"
#include "GameObjects/Water.h"
#include "GameObjects/Eagle.h"
#include "GameObjects/Border.h"

#include <iostream>
#include <algorithm>
#include <cmath>

std::shared_ptr<GameObjectInterface> CreateGameObjectFromMarkup(const char markup, const glm::vec2& position, const glm::vec2& size, const float rotation)
{
    switch (markup)
    {
    case '0':
        return std::make_shared<WallGameObject>(WallGameObject::WallGOType::Right, position, size, rotation, 0.f);
    case '1':
        return std::make_shared<WallGameObject>(WallGameObject::WallGOType::Bottom, position, size, rotation, 0.f);
    case '2':
        return std::make_shared<WallGameObject>(WallGameObject::WallGOType::Left, position, size, rotation, 0.f);
    case '3':
        return std::make_shared<WallGameObject>(WallGameObject::WallGOType::Top, position, size, rotation, 0.f);
    case '4':
        return std::make_shared<WallGameObject>(WallGameObject::WallGOType::All, position, size, rotation, 0.f);
    case '5':
        return std::make_shared<ConcreteWallGameObject>(ConcreteWallGameObject::WallGOType::Right, position, size, rotation, 0.f);
    case '6':
        return std::make_shared<ConcreteWallGameObject>(ConcreteWallGameObject::WallGOType::Bottom, position, size, rotation, 0.f);
    case '7':
        return std::make_shared<ConcreteWallGameObject>(ConcreteWallGameObject::WallGOType::Left, position, size, rotation, 0.f);
    case '8':
        return std::make_shared<ConcreteWallGameObject>(ConcreteWallGameObject::WallGOType::Top, position, size, rotation, 0.f);
    case '9':
        return std::make_shared<ConcreteWallGameObject>(ConcreteWallGameObject::WallGOType::All, position, size, rotation, 0.f);
    case 'A':
        return std::make_shared<Water>(position, size, rotation, 0.f);
    case 'B':
        return std::make_shared<Trees>(position, size, rotation, 1.f);
    case 'C':
        return std::make_shared<Ice>(position, size, rotation, -1.f);
    case 'E':
        return std::make_shared<Eagle>(position, size, rotation, 0.f);
    case 'G':
        return std::make_shared<WallGameObject>(WallGameObject::WallGOType::BottomLeft, position, size, rotation, 0.f);
    case 'H':
        return std::make_shared<WallGameObject>(WallGameObject::WallGOType::BottomRight, position, size, rotation, 0.f);
    case 'I':
        return std::make_shared<WallGameObject>(WallGameObject::WallGOType::TopLeft, position, size, rotation, 0.f);
    case 'J':
        return std::make_shared<WallGameObject>(WallGameObject::WallGOType::TopRight, position, size, rotation, 0.f);
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
    widthPixels = static_cast<unsigned int>(width * BLOCK_SIZE);
    heightPixels = static_cast<unsigned int>(height * BLOCK_SIZE);

    playerRespawn1 = { BLOCK_SIZE * (width / 2 - 1), BLOCK_SIZE / 2 };
    playerRespawn2 = { BLOCK_SIZE * (width / 2 + 3), BLOCK_SIZE / 2 };
    enemyRespawn1 = { BLOCK_SIZE, BLOCK_SIZE * height - BLOCK_SIZE / 2 };
    enemyRespawn2 = { BLOCK_SIZE * (width / 2 + 1), BLOCK_SIZE * height - BLOCK_SIZE / 2 };
    enemyRespawn3 = { BLOCK_SIZE * width, BLOCK_SIZE * height - BLOCK_SIZE / 2 };

    levelObjects.reserve(width * height+4);
    unsigned int currentBottomOffset = static_cast<unsigned int>(BLOCK_SIZE * (height - 1) + BLOCK_SIZE / 2.f);
    for (const std::string& currentRow : levelMarkup)
    {
        unsigned int currentLeftOffset = BLOCK_SIZE;
        for (const char currentElement : currentRow)
        {
            switch (currentElement)
            {
            case 'K':
                playerRespawn1 = { currentLeftOffset, currentBottomOffset };
                levelObjects.emplace_back(nullptr);
                break;
            case 'L':
                playerRespawn2 = { currentLeftOffset, currentBottomOffset };
                levelObjects.emplace_back(nullptr);
                break;
            case 'M':
                enemyRespawn1 = { currentLeftOffset, currentBottomOffset };
                levelObjects.emplace_back(nullptr);
                break;
            case 'N':
                enemyRespawn2 = { currentLeftOffset, currentBottomOffset };
                levelObjects.emplace_back(nullptr);
                break;
            case 'O':
                enemyRespawn3 = { currentLeftOffset, currentBottomOffset };
                levelObjects.emplace_back(nullptr);
                break;
            default:
                levelObjects.emplace_back(CreateGameObjectFromMarkup(currentElement, glm::vec2(currentLeftOffset, currentBottomOffset), glm::vec2(BLOCK_SIZE, BLOCK_SIZE), 0.f));
                break;
            }
            currentLeftOffset += BLOCK_SIZE;
        }
        currentBottomOffset -= BLOCK_SIZE;
    }
    // нижн€€ граница
    levelObjects.emplace_back(std::make_shared<Border>(glm::vec2(BLOCK_SIZE, 0.f), glm::vec2(height * BLOCK_SIZE, BLOCK_SIZE / 2.f), 0.f, 0.f));

    // верхн€€ граница
    levelObjects.emplace_back(std::make_shared<Border>(glm::vec2(BLOCK_SIZE, height * BLOCK_SIZE + BLOCK_SIZE / 2.f), glm::vec2(width * BLOCK_SIZE, BLOCK_SIZE / 2.f), 0.f, 0.f));

    // лева€ граница
    levelObjects.emplace_back(std::make_shared<Border>(glm::vec2(0.f, 0.f), glm::vec2(BLOCK_SIZE, (height + 1) * BLOCK_SIZE), 0.f, 0.f));

    // права€ граница
    levelObjects.emplace_back(std::make_shared<Border>(glm::vec2((width + 1) * BLOCK_SIZE, 0.f), glm::vec2(BLOCK_SIZE * 2.f, (height + 1) * BLOCK_SIZE), 0.f, 0.f));
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

void Level::Update(const double delta)
{
    for (const auto& currentLevelObject : levelObjects)
    {
        if (currentLevelObject)
        {
            currentLevelObject->UpdateFrame(delta);
        }
    }
}

size_t Level::GetLevelWidth() const
{
    return (width + 3) * BLOCK_SIZE;
}

size_t Level::GetLevelHeight() const
{
    return (height + 1) * BLOCK_SIZE;
}

std::vector<std::shared_ptr<GameObjectInterface>> Level::GetLevelObjects(const glm::vec2& bottomLeft, const glm::vec2& topRight) const
{
    std::vector<std::shared_ptr<GameObjectInterface>> output;
    output.reserve(9);

    glm::vec2 newBottomLeft(std::clamp(bottomLeft.x - BLOCK_SIZE, 0.f, static_cast<float>(widthPixels)), std::clamp(heightPixels - bottomLeft.y + BLOCK_SIZE / 2, 0.f, static_cast<float>(heightPixels)));
    glm::vec2 newTopRight(std::clamp(topRight.x - BLOCK_SIZE, 0.f, static_cast<float>(widthPixels)), std::clamp(heightPixels - topRight.y + BLOCK_SIZE / 2, 0.f, static_cast<float>(heightPixels)));

    size_t startX = static_cast<size_t>(floor(newBottomLeft.x / BLOCK_SIZE));
    size_t endX = static_cast<size_t>(ceil(newTopRight.x / BLOCK_SIZE));

    size_t startY = static_cast<size_t>(floor(newTopRight.y / BLOCK_SIZE));
    size_t endY = static_cast<size_t>(ceil(newBottomLeft.y / BLOCK_SIZE));

    for (size_t currentColumn = startX; currentColumn < endX; currentColumn++)
    {
        for (size_t currentRow = startY; currentRow < endY; currentRow++)
        {
            auto& currentObject = levelObjects[currentRow * width + currentColumn];
            if (currentObject)
            {
                output.push_back(currentObject);
            }
        }
    }

    if (endX >= width)
    {
        output.push_back(levelObjects[levelObjects.size() - 1]);
    }
    if (startX <= 1)
    {
        output.push_back(levelObjects[levelObjects.size() - 2]);
    }
    if (startY <= 1)
    {
        output.push_back(levelObjects[levelObjects.size() - 3]);
    }
    if (endY >= height)
    {
        output.push_back(levelObjects[levelObjects.size() - 4]);
    }

    return output;
}
