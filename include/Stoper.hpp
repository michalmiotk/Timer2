#pragma once

#include <chrono>

#include "types.hpp"
#include "IStoper.hpp"


template <typename T=secondsDouble>
class Stoper: public IStoper<T>{
public:
    T getElapsedTime() const override;
    void start() override;
private:
    State state{State::stop};
    std::chrono::time_point<std::chrono::steady_clock> startTime;
};

template <typename T>
T Stoper<T>::getElapsedTime() const{
    if(state == State::stop)
    {
        return {};
    }
    return std::chrono::duration_cast<T>(std::chrono::steady_clock::now() - startTime);
}

template <typename T>
void Stoper<T>::start(){
    state = State::start;
    startTime = std::chrono::steady_clock::now();
}
