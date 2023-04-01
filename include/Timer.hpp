#include <functional>
#include <chrono>
#include <thread>
#include <condition_variable>
#include "IRunner.hpp"
#include "Stoper.hpp"

template <typename T=secondsDouble>
struct Timer{
    Timer(IRunner<T>& runner): runner(runner){};
    void start(std::function<void(void)>&&, T);
    void stop();
    T getElapsedTime() const;
private:
    IRunner<T>& runner;
    Stoper<T> stoper;
    std::jthread t;
    State state{State::stop};
};


template <typename T>
void Timer<T>::start(std::function<void(void)>&& fn, T interval){
    if(state==State::start)
    {
        return;
    }
    stoper.start();
    t = std::jthread(&IRunner<T>::run, std::ref(runner), std::forward<std::function<void(void)>>(fn), interval);
    state = State::start;
}

template <typename T>
void Timer<T>::stop(){
    if(state == State::stop){
        return;
    }
    state = State::stop;
    stoper.stop();
    runner.stop();
}

template <typename T>
T Timer<T>::getElapsedTime() const{
   return stoper.getElapsedTime();
}
