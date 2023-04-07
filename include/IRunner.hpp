#pragma once 
#include <functional>
#include <chrono>
#include <condition_variable>

#include "types.hpp"


template <typename Interval, typename Function, typename ... Args>
class IRunner{
public:
    virtual void stop() = 0;
    virtual void run(Function fn, Interval timeToStart, Args...) = 0;
    virtual ~IRunner();
};

template <typename Interval, typename Function, typename ... Args>
IRunner<Interval, Function, Args...>::~IRunner()
{
}
