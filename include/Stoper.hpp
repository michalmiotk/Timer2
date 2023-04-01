#include <chrono>

#include "types.hpp"

template <typename T=secondsDouble>
struct Stoper{
    T getElapsedTime() const;
    void start();
    void stop();
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
