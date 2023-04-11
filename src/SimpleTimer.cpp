#include "SimpleTimer.hpp"


void SimpleTimer::start(){
    if(state==State::start)
    {
        return;
    }
    stoper->start();
    t = std::jthread(&IRunner<std::chrono::milliseconds, std::function<void(void)>>::run, std::ref(*runner), callable, timeToCall);
    state = State::start;
}

void SimpleTimer::stop(){
    if(state == State::stop){
        return;
    }
    state = State::stop;
    runner->stop();
}

secondsDouble SimpleTimer::getElapsedTime() const{
    return stoper->getElapsedTime();
}

SimpleTimer::SimpleTimer(std::chrono::milliseconds time, std::function<void(void)> function, std::unique_ptr<IRunner<std::chrono::milliseconds, std::function<void(void)>>> runner, std::unique_ptr<IStoper> stoper):
    timeToCall(time), callable(function), runner(std::move(runner)), stoper(std::move(stoper)){};
