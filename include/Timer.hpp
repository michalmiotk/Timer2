#pragma once

#include "types.hpp"
#include "OneShotRunner.hpp"

class Timer{
public:
    Timer(TimerType, milliseconds);
    void start();
    void stop();
    void setTime(milliseconds);
    secondsDouble getElapsedTime();
private:
    TimerType type;
    milliseconds time;
    Stoper stoper;
};

Timer::Timer(TimerType type, milliseconds time): type(type), time(time)
{

}

void Timer::start()
{
    stoper.start();
}

void Timer::stop()
{
}

void Timer::setTime(milliseconds newTime){
    time = newTime;
}

secondsDouble Timer::getElapsedTime()
{
    return stoper.getElapsedTime();
}
