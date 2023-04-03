#include <functional>
#include <chrono>
#include <thread>
#include <memory>
#include <condition_variable>

#include "IRunner.hpp"
#include "Stoper.hpp"
#include "ITimer.hpp"


template <typename TimerInterval=std::chrono::milliseconds, typename T=secondsDouble>
class Timer: public ITimer<TimerInterval, T>{
public:
    Timer(std::unique_ptr<IRunner<TimerInterval>> runner, std::unique_ptr<IStoper<T>> stoper): runner(std::move(runner)), stoper(std::move(stoper)){};
    void start(std::function<void(void)>, TimerInterval);
    void stop();
    T getElapsedTime() const;
private:
    std::unique_ptr<IRunner<TimerInterval>> runner;
    std::unique_ptr<IStoper<T>> stoper;
    std::jthread t;
    State state{State::stop};
};


template <typename TimerInterval, typename T>
void Timer<TimerInterval, T>::start(std::function<void(void)> fn, TimerInterval interval){
    if(state==State::start)
    {
        return;
    }
    stoper->start();
    t = std::jthread(&IRunner<TimerInterval>::run, std::ref(*runner), fn, interval);
    state = State::start;
}

template <typename TimerInterval, typename T>
void Timer<TimerInterval, T>::stop(){
    if(state == State::stop){
        return;
    }
    state = State::stop;
    runner->stop();
}

template <typename TimerInterval, typename T>
T Timer<TimerInterval, T>::getElapsedTime() const{
   return stoper->getElapsedTime();
}
