#include "GameObjectInterface.h"

GameObjectInterface::GameObjectInterface(const glm::vec2& position, const glm::vec2& size, const float rotation, const float layer)
                                                                                                                                    : GOIposition(position)
                                                                                                                                    , GOIsize(size)
                                                                                                                                    , GOIrotation(rotation)
                                                                                                                                    , GOIlayer(layer)
                                                                                                                                
{
}

GameObjectInterface::~GameObjectInterface()
{
}