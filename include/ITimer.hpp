#include <chrono>
#include <functional>

#include "types.hpp"


template <typename TimerInterval=std::chrono::milliseconds, typename T=secondsDouble, typename Function=std::function<void(void)>>
class ITimer{
public:
    void start(Function, TimerInterval);
    void stop();
    T getElapsedTime() const;
    virtual ~ITimer();
};

template <typename TimerInterval, typename T, typename Function>
ITimer<TimerInterval, T, Function>::~ITimer()
{
}
