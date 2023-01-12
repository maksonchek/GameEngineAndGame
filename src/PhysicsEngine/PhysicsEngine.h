#pragma once
#include <unordered_set>
#include <memory>
#include <glm/vec2.hpp>
#include <vector>

class GameObjectInterface;
class Level;

namespace PhysicsEngineManager {

    /*!
    * \brief ���������, �������� ���������� ���������� �� �������
    */
    struct BoxCollider
    {
        BoxCollider(const glm::vec2& bottomLeft, const glm::vec2& topRight);
        glm::vec2 bottomLeft;
        glm::vec2 topRight;
    };

    /*!
    * \brief �����, ���������� �� �������������� ������� �������� � ������� � ���� � ������. �����������
    */
    class PhysicsEngine {
    public:
        PhysicsEngine() = delete;
        ~PhysicsEngine() = delete;

        PhysicsEngine(const PhysicsEngine&) = delete;

        PhysicsEngine& operator=(const PhysicsEngine&) = delete;

        PhysicsEngine& operator=(PhysicsEngine&&) = delete;

        PhysicsEngine(PhysicsEngine&&) = delete;

        /*!
        * �����, �������������� ������ ���� �� ����� ���� � �����������, ���� �� �������������� ��������. ���� ����, ����������� �� ��������������
        * \param delta - ������� ������� �����
        * ����������:
        * \code
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
        \endcode
        */
        static void Update(const double delta);

        /*!
        * ��������� � ��� ���������� �� �������, ��������� �����������������, pGameObject - ��� ���� ������
        * \param pGameObject - ����� ��������� �� ������, ������� ���� ��������
        * ����������:
        * \code
            dynamicObjects.insert(std::move(pGameObject));
        * \endcode
        */
        static void AddDynamicGameObject(std::shared_ptr<GameObjectInterface> pGameObject);

        /*!
        * ������� ������ �� ������ � ���� � ������� ��������
        * ����������:
        * \code
                dynamicObjects.clear();
                pCurrentLevel.reset();
        * \endcode
        */
        static void DeleteAll();
        
        /*!
        * �����, ���������� pCurrentLevel �������� �������, � ������ ������������ ������� � pLevel
        * \param pLevel - ��������� �� �������
        * ����������:
        * \code
        *         pCurrentLevel.swap(pLevel);
        * \endcode
        */
        static void SetCurrentLevel(std::shared_ptr<Level> pLevel);


    private:
        static std::shared_ptr<Level> pCurrentLevel; ///<������� �������, �� ������� ������ �����
        static std::unordered_set<std::shared_ptr<GameObjectInterface>> dynamicObjects; ///< �������, ��������� � ��������������

        /*!
        * ����, ����������� ���� �� � ������� ����� �������������� 2� ��������
        * \param colliders1 - ���������� 1-�� �������, � ������ ��� �������������� (������ ��������� �����, ������������� � �.�
        * \param position1 - ������� 1-�� �������
        * \param colliders2 - ���������� 2-�� �������
        * \parm position2 - ������� 2-�� �������
        * \return ������� ��������, ���� �� �������������� ����� ����� ����� ��������� ��� ���
        * ����������:
        * \code
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
        * \endcode
        */
        static bool HasInteraction(const std::vector<BoxCollider>& colliders1, const glm::vec2& position1, const std::vector<BoxCollider>& colliders2, const glm::vec2& position2);
    };
}