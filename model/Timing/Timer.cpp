#include <chrono>

#include "Timer.h"

namespace model
{
namespace timing
{

Timer::Timer() :
    counter(0),
    counting(false)
{
}

Timer::~Timer()
{
}

void Timer::run()
{
    this->counting = true;
    std::chrono::high_resolution_clock::time_point startingTime = std::chrono::high_resolution_clock::now();
    while (this->isCounting())
    {
        std::chrono::high_resolution_clock::time_point currentTime = std::chrono::high_resolution_clock::now();
        std::chrono::high_resolution_clock::duration timeDifference = currentTime - startingTime;
        if (timeDifference >= std::chrono::seconds(1))
        {
            this->counterLock.lock();
            this->counter++;
            this->counterLock.unlock();

            this->notifyListener();
            startingTime = currentTime;
        }
    }
}

void Timer::reset()
{
    this->counterLock.lock();
    this->counter = 0;
    this->counterLock.unlock();
}

void Timer::stop()
{
    this->countingConditionLock.lock();
    this->counting = false;
    this->countingConditionLock.unlock();
}

int Timer::getSecondCount()
{
    this->counterLock.lock();
    int result = this->counter;
    this->counterLock.unlock();
    return result;
}

bool Timer::isCounting()
{
    this->countingConditionLock.lock();
    bool result = this->counting;
    this->countingConditionLock.unlock();
    return result;
}

void Timer::addSecondsIncreasedListener(void (*callback)(void*), void* data)
{
    this->callback = callback;
    this->callbackData = data;
}

void Timer::notifyListener()
{
    if (this->callback != nullptr)
    {
        this->callback(this->callbackData);
    }
}

}
}
