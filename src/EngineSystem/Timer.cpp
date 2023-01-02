#include "Timer.h"

Timer::Timer()
    : isRunning(false)
    , timeLeft(0)
{

}

void Timer::Update(const double delta)
{
    if (isRunning)
    {
        timeLeft -= delta;
        if (timeLeft <= 0)
        {
            isRunning = false;
            callback();
        }
    }
}

void Timer::Start(const double duration)
{
    timeLeft = duration;
    isRunning = true;
}

void Timer::SetCallback(std::function<void()> callback)
{
    this->callback = callback;
}