#pragma once

#include <functional>

/*!
* \brief Класс, необходимый для событий/анимаций в игре, которые незациклены и не длятся бесконечно. Чтобы их можно было остановить
*/
class Timer {
public:
    Timer();

    /*!
    * Функция проверяющийся, истёкло ли время таймера. Включает
    * \param delta -единица времени кадра
    * Реализация:
    * \code
             if (isRunning)
            {
                timeLeft -= delta;
                if (timeLeft <= 0)
                {
                    isRunning = false;
                    callback();
                }
            }
    * \endcode
    */
    void Update(const double delta);

    /*!
    * Функция, запускающая таймер
    * \param duration - длительность таймера
    * \code
        timeLeft = duration;
        isRunning = true;
    * \endcode
    */
    void Start(const double duration);

    /*!
    * Получает и устанавливает в таймере функцию обратного отклика
    */
    void SetCallback(std::function<void()> callback);

private:
    std::function<void()> callback; ///< Функция обратного вызова, нужная для включения/выключения таймера
    double timeLeft; ///< Время длительности ограниченного по времени события
    bool isRunning; ///< Включён ли таймер или нет
};
