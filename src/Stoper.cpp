#include "Stoper.hpp"


secondsDouble Stoper::getElapsedTime() const{
    if(state == State::stop)
    {
        return {};
    }
    using secondsDoubleChrono = std::chrono::duration<double>;
    auto elapsedTime = std::chrono::duration_cast<secondsDoubleChrono>(std::chrono::steady_clock::now() - startTime);
    return elapsedTime.count();
}

void Stoper::start(){
    state = State::start;
    startTime = std::chrono::steady_clock::now();
}
