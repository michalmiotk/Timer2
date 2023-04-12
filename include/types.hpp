#pragma once
#include <chrono>


using secondsDouble = double;
using milliseconds = int;
enum class State{
    start,
    stop
};

enum class TimerType{
    recurrent,
    oneShot
};