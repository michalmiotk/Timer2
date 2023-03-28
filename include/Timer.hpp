#include <iostream>
#include <functional>
#include <chrono>
#include <thread>
#include <mutex>
#include <condition_variable>
#include "IRunner.hpp"

enum class State{
    start,
    stop
};

template <typename T=secondsDouble>
struct Timer{
    Timer(IRunner<T>& runner): runner(runner){};
    void start(std::function<void(void)>&&, T);
    void stop();
    T getElapsedTime() const;
private:
    IRunner<T>& runner;
    std::chrono::time_point<std::chrono::steady_clock> startTime;
    std::chrono::time_point<std::chrono::steady_clock> stopTime;
    std::jthread t;
    State state{State::stop};
};


template <typename T>
void Timer<T>::start(std::function<void(void)>&& fn, T interval){
    if(state==State::start)
    {
        return;
    }
    startTime = std::chrono::steady_clock::now();
    t = std::jthread(&IRunner<T>::run, std::ref(runner), std::forward<std::function<void(void)>>(fn), interval);
    state = State::start;
}

template <typename T>
void Timer<T>::stop(){
    if(state == State::stop){
        return;
    }
    state = State::stop;
    stopTime = std::chrono::steady_clock::now();
    runner.stop();
}

template <typename T>
T Timer<T>::getElapsedTime() const{
    if(state == State::stop)
    {
        std::cout<<"state stop";
        auto timeDiff = stopTime - startTime;
        return std::chrono::duration_cast<T>(timeDiff);
    }
    return std::chrono::duration_cast<T>(std::chrono::steady_clock::now() - startTime);
}