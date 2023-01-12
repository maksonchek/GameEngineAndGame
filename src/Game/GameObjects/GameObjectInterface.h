#pragma once 

#include <glm/vec2.hpp>
#include"../../PhysicsEngine/PhysicsEngine.h"

/*!
* \brief Виртуальный класс, создержащий в себе поля и методы, общие для всех возможных игровых объектов. Является связующим звеном между объектом и физическим движком. 
Наследование от этого класса при срздании игрового объекта обязательно!
*/
class GameObjectInterface 
{
public:
    /*!
    * \brief Класс, хранящий перечисления типов игровых объектов (Подвижный, способный к взаимодействию объект, подвижный неспособный к взаимодействию объект,
    * неподвижный, способный к взаимодействию объект, непоодвижный неспособный к взаимодействию объект)
    */
    enum class ObjectType
    {
        Constant_Satic_Object,
        Constant_Dynamic_Object,
        Temporary_Satic_Object,
        Temporary_Dynamic_Object,
    };

    /*!
    * Конструктор класса принимет следующие параметры:
    * \param objectType - тип объекта
    * \param position - позиция объекта
    * \param size - размер объекта
    * \param rotation - поворот объекта
    * \param layer - слой объекта
    * Больше в конструкторе ничего не происходит
    */
    GameObjectInterface(const ObjectType objectType, const glm::vec2& position, const glm::vec2& size, const float rotation, const float layer);

    /*!
    * Функция, отвечающая за отрисовку объекта, которую разработчик должен будет переопределить
    */
    virtual void Render() const = 0;

    /*!
    * Функция, обработку физики объекта каждый кадр, которую разработчик должен будет переопределить
    */
    virtual void UpdateFrame(const double delta) {};

    /*!
    * Возвращает текущую позицию объекта
    */
    virtual glm::vec2& GetCurrentPosition();

    /*!
    * Возвращает текущий поворот объекта
    */
    virtual glm::vec2& GetCurrentDirection();

    /*!
    * Возвращает скорость объекта
    */
    virtual double GetCurrentVelocity();

    /*!
    * Устанавливает на объекте новую скорость
    */
    virtual void SetVelocity(const double velocity);
    
    /*!
    * Возвращает коллайдеры объекта
    */
    const std::vector<PhysicsEngineManager::BoxCollider>& GetColliders() const
    {
        return boxColliders;
    }

    /*!
    * Возвращает координаты границ объеткта - т.е его размер 
    */
    const glm::vec2& GetSize() const 
    { 
        return GOIsize;
    }

    /*!
    * Возвращает тип объекта
    */
    ObjectType GetObjectType() const 
    { 
        return GOIobjectType;
    }

    /*!
    * Вункция, возвращающая значение, относительно типа объекта, может ли объект взаимодействовать с другими
    */
    virtual bool IsCollides(const ObjectType objectType) 
    {
        return true; 
    }

    /*!
    * Возвращает булевое значение, находится ли объект во взаимодействии сейчас или нет
    */
    virtual void OnCollision() 
    {

    }

    virtual ~GameObjectInterface();

protected:
    glm::vec2 GOIposition; ///<Позиция объекта
    glm::vec2 GOIsize; ///<Размер объекта
    glm::vec2 GOIdirection; ///<Поворот объекта
    ObjectType GOIobjectType; ///<Тип объекта
    double GOIvelocity; ///<Скорость объекта
    float GOIrotation; ///<Поворот объекта
    float GOIlayer; ///<Слой объекта
    std::vector<PhysicsEngineManager::BoxCollider> boxColliders; ///<Коллайдеры объекта
};