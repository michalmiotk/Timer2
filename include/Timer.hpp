#include <functional>
#include <chrono>
#include <thread>
#include <condition_variable>
#include "IRunner.hpp"
#include "Stoper.hpp"
#include <memory>


template <typename T=secondsDouble>
class Timer{
public:
    Timer(std::unique_ptr<IRunner<T>> runner, std::unique_ptr<IStoper<T>> stoper): runner(std::move(runner)), stoper(std::move(stoper)){};
    void start(std::function<void(void)>&&, T);
    void stop();
    T getElapsedTime() const;
private:
    std::unique_ptr<IRunner<T>> runner;
    std::unique_ptr<IStoper<T>> stoper;
    std::jthread t;
    State state{State::stop};
};


template <typename T>
void Timer<T>::start(std::function<void(void)>&& fn, T interval){
    if(state==State::start)
    {
        return;
    }
    stoper->start();
    t = std::jthread(&IRunner<T>::run, std::ref(*runner), std::forward<std::function<void(void)>>(fn), interval);
    state = State::start;
}

template <typename T>
void Timer<T>::stop(){
    if(state == State::stop){
        return;
    }
    state = State::stop;
    stoper->stop();
    runner->stop();
}

template <typename T>
T Timer<T>::getElapsedTime() const{
   return stoper->getElapsedTime();
}
