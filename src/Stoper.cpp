#include "Stoper.hpp"


secondsDouble Stoper::getElapsedTime() const{
    if(isStarted == false)
    {
        return {};
    }
    using secondsDoubleChrono = std::chrono::duration<double>;
    auto elapsedTime = std::chrono::duration_cast<secondsDoubleChrono>(std::chrono::steady_clock::now() - startTime);
    return elapsedTime.count();
}

void Stoper::start(){
    isStarted = true;
    startTime = std::chrono::steady_clock::now();
}
