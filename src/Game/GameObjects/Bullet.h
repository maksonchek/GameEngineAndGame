#pragma once

#include "GameObjectInterface.h"

#include <array>
#include <memory>

namespace RenderEngine {
    class Sprite;
}

class Bullet : public GameObjectInterface {
public:
    enum class ObjectOrientation : uint8_t { //Ориентация пули
        Top,
        Bottom,
        Left,
        Right
    };

    Bullet(const double velocity, const glm::vec2& position, const glm::vec2& size, const float layer);
    virtual void Render() const override;
    bool IsActive() const { return isActive; }
    void Fire(const glm::vec2& position, const glm::vec2& direction); //Создание пули с ориентацие на позиции танка
    virtual void OnCollision() override; //Проверка объекта на взаимодействие с другим. Наследуемый от GameObjectInterface метод

private:
    std::shared_ptr<RenderEngine::Sprite> pSprite_top;
    std::shared_ptr<RenderEngine::Sprite> pSprite_bottom;
    std::shared_ptr<RenderEngine::Sprite> pSprite_left;
    std::shared_ptr<RenderEngine::Sprite> pSprite_right;
    ObjectOrientation objectOrientation;
    double maxVelocity; //Максимальная скорость пули
    bool isActive; // Активна ли она
};