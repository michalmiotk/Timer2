#include "Stoper.hpp"


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
