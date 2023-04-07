#pragma once

#include <chrono>

#include "types.hpp"
#include "IStoper.hpp"


class Stoper: public IStoper{
public:
    secondsDouble getElapsedTime() const override;
    void start() override;
private:
    State state{State::stop};
    std::chrono::time_point<std::chrono::steady_clock> startTime;
};


secondsDouble Stoper::getElapsedTime() const{
    if(state == State::stop)
    {
        return {};
    }
    return std::chrono::duration_cast<secondsDouble>(std::chrono::steady_clock::now() - startTime);
}

void Stoper::start(){
    state = State::start;
    startTime = std::chrono::steady_clock::now();
}
