#pragma once 
#include <functional>
#include <chrono>
#include <condition_variable>

#include "types.hpp"


template <typename Interval, typename Callback>
class IRunner{
public:
    virtual void stop() = 0;
    virtual void run(Callback&& fn, Interval timeToStart) = 0;
    virtual ~IRunner();
};

template <typename Interval, typename Callback>
IRunner<Interval, Callback>::~IRunner()
{
}
