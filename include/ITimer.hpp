#include <chrono>

#include "types.hpp"


template <typename TimerInterval=std::chrono::milliseconds, typename T=secondsDouble>
class ITimer{
public:
    void start(std::function<void(void)>, TimerInterval);
    void stop();
    T getElapsedTime() const;
    virtual ~ITimer();
};

template <typename TimerInterval, typename T>
ITimer<TimerInterval, T>::~ITimer()
{
}
