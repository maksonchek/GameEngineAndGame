#pragma once 

#include <glm/vec2.hpp>
#include"../../PhysicsEngine/PhysicsEngine.h"

class GameObjectInterface 
{
public:
    enum class ObjectType
    {
        Constant_Satic_Object,
        Constant_Dynamic_Object,
        Temporary_Satic_Object,
        Temporary_Dynamic_Object,
    };
    GameObjectInterface(const ObjectType objectType, const glm::vec2& position, const glm::vec2& size, const float rotation, const float layer);
    virtual void Render() const = 0;
    virtual void UpdateFrame(const double delta) {};

    virtual glm::vec2& GetCurrentPosition();

    virtual glm::vec2& GetCurrentDirection();

    virtual double GetCurrentVelocity();

    virtual void SetVelocity(const double velocity);
    
    const std::vector<PhysicsEngineManager::BoxCollider>& GetColliders() const
    {
        return boxColliders;
    }


    const glm::vec2& GetSize() const 
    { 
        return GOIsize;
    }

    ObjectType GetObjectType() const 
    { 
        return GOIobjectType;
    }
    virtual bool IsCollides(const ObjectType objectType) 
    {
        return true; 
    }
    virtual void OnCollision() 
    {

    }

    virtual ~GameObjectInterface();

protected:
    glm::vec2 GOIposition;
    glm::vec2 GOIsize;
    glm::vec2 GOIdirection;
    ObjectType GOIobjectType;
    double GOIvelocity;
    float GOIrotation;
    float GOIlayer;
    std::vector<PhysicsEngineManager::BoxCollider> boxColliders;
};