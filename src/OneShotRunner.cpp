#include "OneShotRunner.hpp"

void OneShotRunner::stop(){
    stopPromise.set_value();
}

void OneShotRunner::run(std::function<void()>&& fn, milliseconds timeToStart){
    if(timeToStart<0){
        throw IntervalLessThanZero{};
    }
    if(stopFuture.wait_for(std::chrono::milliseconds{timeToStart}) == std::future_status::timeout){
        fn();
    }
}

OneShotRunner::OneShotRunner(){
    stopFuture = stopPromise.get_future();
}