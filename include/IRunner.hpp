#pragma once 
#include <functional>
#include <chrono>
#include <condition_variable>

#include "types.hpp"


template <typename Interval, typename Callback, typename ... Args>
class IRunner{
public:
    virtual void stop() = 0;
    virtual void run(Callback&& fn, Interval timeToStart, Args&&...) = 0;
    virtual ~IRunner();
};

template <typename Interval, typename Callback, typename ... Args>
IRunner<Interval, Callback, Args...>::~IRunner()
{
}
