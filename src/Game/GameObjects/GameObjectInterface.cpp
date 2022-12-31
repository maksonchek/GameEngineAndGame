#include "GameObjectInterface.h"

GameObjectInterface::GameObjectInterface(const glm::vec2& position, const glm::vec2& size, const float rotation)
    : GOIposition(position)
    , GOIsize(size)
    , GOIrotation(rotation)
{
}

GameObjectInterface::~GameObjectInterface()
{
}