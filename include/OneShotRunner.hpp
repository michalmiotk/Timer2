#pragma once

#include <functional>
#include <chrono>
#include <future>


#include "IRunner.hpp"
#include "IntervalLessThanZero.hpp"
#include "types.hpp"

class OneShotRunner: public IRunner{
public:
    void stop() override; 
    void run(std::function<void()>&&, milliseconds timeToStart) override;
    OneShotRunner();
private:
    std::promise<void> stopPromise;
    std::future<void> stopFuture;
};
