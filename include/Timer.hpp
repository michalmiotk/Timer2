#include <iostream>
#include <functional>
#include <linux/timerfd.h>
#include <chrono>
#include <thread>
#include <mutex>
#include <condition_variable>

using secondsDouble = std::chrono::duration<double>;

enum class State{
    start,
    stop
};

template <typename T=secondsDouble>
struct Timer{
    void startOneShot(std::function<void(void)>&&, T);
    void startRecurrent(std::function<void(void)>&&, T);
    void stop();
    T getElapsedTime() const;
private:
    std::chrono::time_point<std::chrono::steady_clock> startTime;
    std::chrono::time_point<std::chrono::steady_clock> stopTime;
    std::condition_variable cv;
    std::jthread t;
    State state{State::stop};
    void internalOneShot(std::function<void(void)>&&, T);
    void internalRecurrent(std::function<void(void)>&&, T);
};

template <typename T>
void Timer<T>::startOneShot(std::function<void(void)>&& fn, T timeToStart){
    if(state==State::start)
    {
        return;
    }
    startTime = std::chrono::steady_clock::now();
    t = std::jthread(&Timer::internalOneShot, this, std::forward<std::function<void(void)>>(fn), timeToStart);
    state = State::start;
}

template <typename T>
void Timer<T>::startRecurrent(std::function<void(void)>&& fn, T interval){
    if(state==State::start)
    {
        return;
    }
    startTime = std::chrono::steady_clock::now();
    t = std::jthread(&Timer::internalRecurrent, this, std::forward<std::function<void(void)>>(fn), interval);
    state = State::start;
}

template <typename T>
void Timer<T>::stop(){
    if(state == State::stop){
        return;
    }
    state = State::stop;
    stopTime = std::chrono::steady_clock::now();
    cv.notify_one();
}

template <typename T>
T Timer<T>::getElapsedTime() const{
    using ms = std::chrono::milliseconds;
    if(state == State::stop)
    {
        std::cout<<"state stop";
        auto timeDiff = stopTime - startTime;
        return std::chrono::duration_cast<T>(timeDiff);
    }
    return std::chrono::duration_cast<T>(std::chrono::steady_clock::now() - startTime);
}

template <typename T>
void Timer<T>::internalOneShot(std::function<void(void)>&& fn, T timeToStart)
{
    std::mutex m;
    std::unique_lock<std::mutex> l(m);
    auto status = cv.wait_for(l, timeToStart);
    if(status == std::cv_status::timeout){
        fn();
    }else{
        if(status == std::cv_status::no_timeout)
        {
            std::cout<<"somebody pressed stop"<<std::endl;
        }
    }
}

template <typename T>
void Timer<T>::internalRecurrent(std::function<void(void)>&& fn, T interval)
{
    std::mutex m;
    std::unique_lock<std::mutex> l(m);
    bool stopped = false;
    while(not stopped){
        if(cv.wait_for(l, interval) == std::cv_status::timeout){
            fn();
            std::cout<<getElapsedTime().count()<<std::endl;
        }else{
            std::cout<<"somebody pressed stop"<<std::endl;
            stopped = true;
        }
    }
}