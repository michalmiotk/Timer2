#include "SimpleTimer.hpp"


SimpleTimer::SimpleTimer(const TimerType type, const milliseconds time, const std::function<void(void)> callable) : type(type), time(time), callable(callable)
{
    stopFuture = stopPromise.get_future();
}

void SimpleTimer::start()
{
    if(state == State::start){
        return;
    }
    stoper.start();
    if (time < 0)
    {
        throw IntervalLessThanZero{};
    }
    t = std::jthread(&SimpleTimer::oneShotCall, this, time);
    state = State::start;
}

void SimpleTimer::oneShotCall(const milliseconds timeToWait)
{
    if (stopFuture.wait_for(std::chrono::milliseconds{timeToWait}) == std::future_status::timeout)
    {
        callable();
    }
    state = State::stop;
}

void SimpleTimer::stop()
{
    if(state == State::stop){
        return;
    }
    stopPromise.set_value();
    if(t.joinable()){
        t.join();
    }
    state = State::stop;
    stopPromise = std::promise<void>();
    stopFuture = stopPromise.get_future();
}

void SimpleTimer::setTime(const milliseconds newTime)
{
    time = newTime;
}

secondsDouble SimpleTimer::getElapsedTime() const
{
    return stoper.getElapsedTime();
}


SimpleTimer::~SimpleTimer()
{
    stop();
}
