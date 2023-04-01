#pragma once

#include <chrono>

#include "types.hpp"
#include "IStoper.hpp"


template <typename T=secondsDouble>
class Stoper: public IStoper<T>{
public:
    T getElapsedTime() const override;
    void start() override;
    void stop() override;
private:
    State state{State::stop};
    std::chrono::time_point<std::chrono::steady_clock> startTime;
    std::chrono::time_point<std::chrono::steady_clock> stopTime;
};

template <typename T>
T Stoper<T>::getElapsedTime() const{
    if(state == State::stop)
    {
        auto timeDiff = stopTime - startTime;
        return std::chrono::duration_cast<T>(timeDiff);
    }
    return std::chrono::duration_cast<T>(std::chrono::steady_clock::now() - startTime);
}

template <typename T>
void Stoper<T>::start(){
    state = State::start;
    startTime = std::chrono::steady_clock::now();
}

template <typename T>
void Stoper<T>::stop(){
    state = State::stop;
}
