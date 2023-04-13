#pragma once

#include <chrono>

#include "types.hpp"


class Stoper{
public:
    secondsDouble getElapsedTime() const;
    void start();
private:
    bool isStarted{false}; 
    std::chrono::time_point<std::chrono::steady_clock> startTime;
};
