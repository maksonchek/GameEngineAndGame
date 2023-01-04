#include "Eagle.h"

#include "../../Resources/ResourceManager.h"
#include "../../Renderer/Sprite.h"

Eagle::Eagle(const glm::vec2& position, const glm::vec2& size, const float rotation, const float layer)
    : GameObjectInterface(position, size, rotation, layer) , sprite{ ResourceManager::GetSprite("eagle"),
                ResourceManager::GetSprite("eagle_dead") } , currentState(EagleState::Alive)
{
    boxColliders.emplace_back(glm::vec2(0), GOIsize);
}

void Eagle::Render() const
{
    sprite[static_cast<size_t>(currentState)]->Render(GOIposition, GOIsize, GOIrotation, GOIlayer);
}

void Eagle::UpdateFrame(const double delta)
{

}