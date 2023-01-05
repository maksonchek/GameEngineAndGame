#include "LevelInterface.h"
#include "GameObjects/GameObjectInterface.h"
#include <algorithm>

LevelInterface::LevelInterface()
{
}

void LevelInterface::Render() const
{
    for (const auto & currentLevelObject : levelObjects)
    {
        if (currentLevelObject)
        {
            currentLevelObject->Render();
        }
    }
}

void LevelInterface::Update(const double delta)
{
    for (const auto& currentLevelObject : levelObjects)
    {
        if (currentLevelObject)
        {
            currentLevelObject->UpdateFrame(delta);
        }
    }
}

size_t LevelInterface::GetLevelWidth() const
{
    return (width + 3) * BLOCK_SIZE;
}

size_t LevelInterface::GetLevelHeight() const
{
    return (height + 1) * BLOCK_SIZE;
}

std::vector<std::shared_ptr<GameObjectInterface>> LevelInterface::GetLevelObjects(const glm::vec2& bottomLeft, const glm::vec2& topRight) const
{
    std::vector<std::shared_ptr<GameObjectInterface>> returnLevelObjects;
    returnLevelObjects.reserve(9);

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
                returnLevelObjects.push_back(currentObject);
            }
        }
    }

    if (endX >= width)
    {
        returnLevelObjects.push_back(levelObjects[levelObjects.size() - 1]);
    }
    if (startX <= 1)
    {
        returnLevelObjects.push_back(levelObjects[levelObjects.size() - 2]);
    }
    if (startY <= 1)
    {
        returnLevelObjects.push_back(levelObjects[levelObjects.size() - 3]);
    }
    if (endY >= height)
    {
        returnLevelObjects.push_back(levelObjects[levelObjects.size() - 4]);
    }

    return returnLevelObjects;
}
