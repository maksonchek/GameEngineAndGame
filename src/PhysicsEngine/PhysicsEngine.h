#pragma once
#include <unordered_set>
#include <memory>
#include <glm/vec2.hpp>
#include <vector>

class GameObjectInterface;
class Level;

namespace PhysicsEngineManager {

    struct BoxCollider
    {
        BoxCollider(const glm::vec2& bottomLeft, const glm::vec2& topRight);
        glm::vec2 bottomLeft;
        glm::vec2 topRight;
    };

    class PhysicsEngine {
    public:
        PhysicsEngine() = delete;
        ~PhysicsEngine() = delete;

        PhysicsEngine(const PhysicsEngine&) = delete;

        PhysicsEngine& operator=(const PhysicsEngine&) = delete;

        PhysicsEngine& operator=(PhysicsEngine&&) = delete;

        PhysicsEngine(PhysicsEngine&&) = delete;

        static void InitPhysics();

        static void Update(const double delta);

        static void AddDynamicGameObject(std::shared_ptr<GameObjectInterface> pGameObject);

        static void DeleteAll();

        static void SetCurrentLevel(std::shared_ptr<Level> pLevel);


    private:
        static std::shared_ptr<Level> pCurrentLevel;
        static std::unordered_set<std::shared_ptr<GameObjectInterface>> dynamicObjects;
        static bool HasInteraction(const std::vector<BoxCollider>& colliders1, const glm::vec2& position1, const std::vector<BoxCollider>& colliders2, const glm::vec2& position2);
    };
}