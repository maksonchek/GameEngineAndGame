#include "PhysicsEngine.h"
#include "../Game/Level.h"

#include "../Game/GameObjects/GameObjectInterface.h"

namespace PhysicsEngineManager {
    std::unordered_set<std::shared_ptr<GameObjectInterface>> PhysicsEngine::dynamicObjects;
    std::shared_ptr<Level> PhysicsEngine::pCurrentLevel;

    void PhysicsEngine::DeleteAll()
    {
        dynamicObjects.clear();
        pCurrentLevel.reset();
    }

    void PhysicsEngine::SetCurrentLevel(std::shared_ptr<Level> pLevel)
    {
        pCurrentLevel.swap(pLevel);
    }

    bool PhysicsEngine::HasInteraction(const std::vector<BoxCollider>& colliders1, const glm::vec2& newPosition1, const std::vector<BoxCollider>& colliders2, const glm::vec2& newPosition2)
    {
        for (const auto& currentCollider1 : colliders1)
        {
            const glm::vec2 currentCollider1_bottomLeft_world = currentCollider1.bottomLeft + newPosition1;
            const glm::vec2 currentCollider1_topRight_world = currentCollider1.topRight + newPosition1;
            for (const auto& currentCollider2 : colliders2)
            {
                const glm::vec2 currentCollider2_bottomLeft_world = currentCollider2.bottomLeft + newPosition2;
                const glm::vec2 currentCollider2_topRight_world = currentCollider2.topRight + newPosition2;
                 
                if (currentCollider1_bottomLeft_world.x >= currentCollider2_topRight_world.x)
                {
                    continue;
                }
                if (currentCollider1_topRight_world.x <= currentCollider2_bottomLeft_world.x)
                {
                    continue;
                }

                if (currentCollider1_bottomLeft_world.y >= currentCollider2_topRight_world.y)
                {
                    continue;
                }
                if (currentCollider1_topRight_world.y <= currentCollider2_bottomLeft_world.y)
                {
                    continue;
                }
                return true;
            }
        }

        return false;
    }

    void PhysicsEngine::InitPhysics()
    {
    }

    void PhysicsEngine::Update(const double delta)
    {
        for (auto& currentObject : dynamicObjects)
        {
            if (currentObject->GetCurrentVelocity() > 0)
            {
                if (currentObject->GetCurrentDirection().x != 0.f) 
                {
                    currentObject->GetCurrentPosition() = glm::vec2(currentObject->GetCurrentPosition().x, static_cast<unsigned int>(currentObject->GetCurrentPosition().y / 4.f + 0.5f) * 4.f);
                }
                else if (currentObject->GetCurrentDirection().y != 0.f) 
                {
                    currentObject->GetCurrentPosition() = glm::vec2(static_cast<unsigned int>(currentObject->GetCurrentPosition().x / 4.f + 0.5f) * 4.f, currentObject->GetCurrentPosition().y);
                }
                const auto newPosition = currentObject->GetCurrentPosition() + currentObject->GetCurrentDirection() * static_cast<float>(currentObject->GetCurrentVelocity() * delta);
                const auto& colliders = currentObject->GetColliders();
                std::vector<std::shared_ptr<GameObjectInterface>> objectsToCheck = pCurrentLevel->GetLevelObjects(newPosition, newPosition + currentObject->GetSize());

                bool hasCollision = false;
                for (const auto& currentObjectToCheck : objectsToCheck)
                {
                    const auto& collidersToCheck = currentObjectToCheck->GetColliders();
                    if (currentObjectToCheck->IsCollides(currentObject->GetObjectType()) && !collidersToCheck.empty())
                    {
                        if (HasInteraction(colliders, newPosition, collidersToCheck, currentObjectToCheck->GetCurrentPosition()))
                        {
                            hasCollision = true;
                            currentObjectToCheck->OnCollision();
                            break;
                        }
                    }
                }

                if (!hasCollision)
                {
                    currentObject->GetCurrentPosition() = newPosition;
                }
                else
                {
                    if (currentObject->GetCurrentDirection().x != 0.f) 
                    {
                        currentObject->GetCurrentPosition() = glm::vec2(static_cast<unsigned int>(currentObject->GetCurrentPosition().x / 8.f + 0.5f) * 8.f, currentObject->GetCurrentPosition().y);
                    }
                    else if (currentObject->GetCurrentDirection().y != 0.f) 
                    {
                        currentObject->GetCurrentPosition() = glm::vec2(currentObject->GetCurrentPosition().x, static_cast<unsigned int>(currentObject->GetCurrentPosition().y / 8.f + 0.5f) * 8.f);
                    }
                    currentObject->OnCollision();
                }
            }
        }
    }

    void PhysicsEngine::AddDynamicGameObject(std::shared_ptr<GameObjectInterface> pGameObject)
    {
        dynamicObjects.insert(std::move(pGameObject));
    }

    BoxCollider::BoxCollider(const glm::vec2& bottomLeft, const glm::vec2& topRight) :bottomLeft(bottomLeft), topRight(topRight)
    {
    }
}