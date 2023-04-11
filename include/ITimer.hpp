#pragma once

#include <chrono>
#include <functional>

#include "types.hpp"

class ITimer{
public:
    virtual void start() = 0;
    virtual void stop() = 0;
    virtual secondsDouble getElapsedTime() const = 0;
    virtual ~ITimer();
};

