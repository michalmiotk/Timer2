#pragma once 
#include <functional>
#include <chrono>
#include <condition_variable>

#include "types.hpp"


template <typename T=secondsDouble>
class IRunner{
public:
    virtual void stop() = 0;
    virtual void run(std::function<void()> fn, T timeToStart) = 0;
};
