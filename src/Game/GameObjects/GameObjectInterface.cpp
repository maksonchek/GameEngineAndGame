#include "GameObjectInterface.h"

GameObjectInterface::GameObjectInterface(const glm::vec2& position, const glm::vec2& size, const float rotation, const float layer)
                                                                                                                                    : GOIposition(position)
                                                                                                                                    , GOIsize(size)
                                                                                                                                    , GOIrotation(rotation)
                                                                                                                                    , GOIlayer(layer)
                                                                                                                                    , GOIdirection(0,1.f)
                                                                                                                                    , GOIvelocity(0)
                                                                                                                                
{
}

glm::vec2& GameObjectInterface::GetCurrentPosition()
{
    return GOIposition;
}

glm::vec2& GameObjectInterface::GetCurrentDirection()
{
    return GOIdirection;
}

double GameObjectInterface::GetCurrentVelocity()
{
    return GOIvelocity;
}

void GameObjectInterface::SetVelocity(const double velocity)
{
    GOIvelocity = velocity;
}

GameObjectInterface::~GameObjectInterface()
{
}