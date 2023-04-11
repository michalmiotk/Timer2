#include <chrono>
#include <functional>

#include "types.hpp"

class ITimer{
public:
    void start();
    void stop();
    secondsDouble getElapsedTime() const;
    virtual ~ITimer();
};

ITimer::~ITimer()
{
}
