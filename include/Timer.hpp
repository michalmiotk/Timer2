#include <functional>
#include <chrono>
#include <thread>
#include <memory>
#include <condition_variable>

#include "IRunner.hpp"
#include "Stoper.hpp"
#include "ITimer.hpp"


template <typename TimerInterval=std::chrono::milliseconds, typename T=secondsDouble, typename Function=std::function<void()>>
class Timer: public ITimer<TimerInterval, T>{
public:
    Timer(std::unique_ptr<IRunner<TimerInterval>> runner, std::unique_ptr<IStoper<T>> stoper): runner(std::move(runner)), stoper(std::move(stoper)){};
    void start(Function, TimerInterval);
    void stop();
    T getElapsedTime() const;
private:
    std::unique_ptr<IRunner<TimerInterval>> runner;
    std::unique_ptr<IStoper<T>> stoper;
    std::jthread t;
    State state{State::stop};
};


template <typename TimerInterval, typename T, typename Function>
void Timer<TimerInterval, T, Function>::start(Function fn, TimerInterval interval){
    if(state==State::start)
    {
        return;
    }
    stoper->start();
    t = std::jthread(&IRunner<TimerInterval>::run, std::ref(*runner), fn, interval);
    state = State::start;
}

template <typename TimerInterval, typename T, typename Function>
void Timer<TimerInterval, T, Function>::stop(){
    if(state == State::stop){
        return;
    }
    state = State::stop;
    runner->stop();
}

template <typename TimerInterval, typename T, typename Function>
T Timer<TimerInterval, T, Function>::getElapsedTime() const{
   return stoper->getElapsedTime();
}
