#pragma once

#include "GameObjectInterface.h"  //Все игровые объекты должны наследовть от GameObjectInterface
#include <memory> //для работы с указателями
#include <array> //Для работы с массивами

namespace RenderEngine {
    class Sprite; //Нам понадобится класс спрайта, поэтому обозначим его в хедере таким образом, а в cpp уже заинклудим. Говорят, это считается хорошим тоном.
}

class ConcreteWallGameObject : public GameObjectInterface { //Все игровые объекты должны наследовть от GameObjectInterface
public:
    enum class WallGOType { //Для удобства создадим перечисления типов стены. Ведь для разных типов разные текстуры.
        All,
        Top,
        Bottom,
        Left,
        Right,
        TopLeft,
        TopRight,
        BottomLeft,
        BottomRight
    };

    enum class WallGOState { //Также создадим перечисления состояний стены. 
        Enabled = 0,
        Destroyed
    };

    enum class WallGOPosition {  //Перечисления позиции стены
        TopLeft,
        TopRight,
        BottomLeft,
        BottomRight
    };
     
    ConcreteWallGameObject(const WallGOType type, const glm::vec2& position, const glm::vec2& size, const float rotation, const float layer); //Коструктор класса. В него понадобится передавать тип, координаты, размеры, поворот и слой отрисовки.
    virtual void Render() const override; //Метод класса GameObjectInterface. Необходим для работы с движком и отрисовки объекта. Его нужно переопределить
    virtual void UpdateFrame(const double delta) override; //Метод класса GameObjectInterface. Необходим для работы с движком и покадровой обработки состояния объекта. Его нужно переопределить

private:

    void RenderWallGo(const WallGOPosition position) const; //Так как у нас разные типы стен, то для каждого типа понадобится свой способ отрисовки спрайта. Разные размеры и текстуры.

    std::array<WallGOState, 4> currentWallGOState; //Текущее состояние объекта. Цел или разрушен
    std::shared_ptr<RenderEngine::Sprite> sprite; //Спрайт стены
    std::array<glm::vec2, 4> offsets; //Так как у нас разные типы стен, то при отрисовке придётся смещать некоторые тектстуры. За это будет отвечть массив смещений для каждго типа
};