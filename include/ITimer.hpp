#include <chrono>
#include <functional>

#include "types.hpp"

class ITimer{
public:
    void start(std::function<void(void)>, std::chrono::milliseconds);
    void stop();
    secondsDouble getElapsedTime() const;
    virtual ~ITimer();
};

ITimer::~ITimer()
{
}
