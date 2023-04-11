#include <functional>
#include <chrono>
#include <thread>
#include <memory>
#include <condition_variable>

#include "IRunner.hpp"
#include "Stoper.hpp"
#include "ITimer.hpp"


class Timer: public ITimer{
public:
    Timer(std::chrono::milliseconds time, std::function<void(void)> function, std::unique_ptr<IRunner<std::chrono::milliseconds, std::function<void(void)>>> runner, std::unique_ptr<IStoper> stoper);
    void start();
    void stop();
    secondsDouble getElapsedTime() const;
private:
    std::chrono::milliseconds timeToCall;
    std::function<void(void)> callable;
    std::unique_ptr<IRunner<std::chrono::milliseconds, std::function<void(void)>>> runner;
    std::unique_ptr<IStoper> stoper;
    std::jthread t;
    State state{State::stop};    
};

