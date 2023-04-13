#pragma once

#include <thread>
#include <future>

#include "IntervalLessThanZero.hpp"
#include "types.hpp"
#include "Stoper.hpp"


class SimpleTimer
{
public:
    SimpleTimer(const TimerType, const milliseconds, const std::function<void(void)>);
    void start();
    void stop();
    void setTime(const milliseconds);
    secondsDouble getElapsedTime() const;
    ~SimpleTimer();
private:
    const TimerType type;
    milliseconds time;
    const std::function<void(void)> callable;
    Stoper stoper;
    std::promise<void> stopPromise;
    std::future<void> stopFuture;
    std::jthread t;
    State state{State::stop};
    void oneShotCall(const milliseconds timeToWait);
};
