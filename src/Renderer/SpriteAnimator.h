#pragma once

#include <memory>

namespace RenderEngine {

    class Sprite;
    /*!
    * \brief Класс, отвечающий за анимацию спрайтов, т.е смену текстуры при опредленных услових и как правило с определенной переодичностью
    */
    class SpriteAnimator {
    public:
        /*!
        * Конструктор класса. В нём просто присваиваются какие-либо значения полям класса
        * \param pSprite - умный указатель на объект спрайта 
        *                                           : 
                                                    pSprite(std::move(pSprite)),  // перемещаем из переданного объекта все данные в объект поля класса
                                                    currentFrame(0), // Начинаем анимацию с первого кадра
                                                    currentFrameDuration(this->pSprite->GetFrameDuration(0)), // Получаем из спрайта длительность кадра
                                                    currentAnimationTime(0) //Начинаем отсчёт с нуля
        */
        SpriteAnimator(std::shared_ptr<Sprite> pSprite);
        size_t GetCurrentFrame() const 
        { 
            return currentFrame; 
        }
        
        /*!
        * Метод, реализующий анимацию покадрово
        * \param - deltaTime время итерации игрового цикла
        * Реализация: 
        * \code
                currentAnimationTime += deltaTime;
                while (currentAnimationTime >= currentFrameDuration)
                {
                    currentAnimationTime -= currentFrameDuration;
                    ++currentFrame;
                    if (currentFrame == pSprite->GetFramesCount())
                    {
                        currentFrame = 0;
                    }
                   currentFrameDuration = pSprite->GetFrameDuration(currentFrame);
                }
        * \endcode
        */
        void Update(const double deltaTime);

    private:
        std::shared_ptr<Sprite> pSprite; ///<умный указатель на объект спрайта
        size_t currentFrame; ///<текущий кадр
        double currentFrameDuration; ///<длительность кадра
        double currentAnimationTime; ///<время всего цикла анимации
    };

}