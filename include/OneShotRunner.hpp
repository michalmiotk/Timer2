#include <functional>
#include <chrono>
#include <future>
#include <cassert>

#include "IRunner.hpp"
#include "IntervalLessThanZero.hpp"


template <typename Interval=std::chrono::milliseconds, typename Callback=std::function<void()>>
class OneShotRunner: public IRunner<Interval, Callback>{
public:
    void stop() override; 
    void run(Callback&&, Interval timeToStart) override;
    OneShotRunner();
private:
    std::promise<void> stopPromise;
    std::future<void> stopFuture;
};

template <typename Interval, typename Callback>
void OneShotRunner<Interval, Callback>::stop(){
    stopPromise.set_value();
}

template <typename Interval, typename Callback>
void OneShotRunner<Interval, Callback>::run(Callback&& fn, Interval timeToStart){
    if(timeToStart.count()<0){
        throw IntervalLessThanZero{};
    }
    if(stopFuture.wait_for(timeToStart) == std::future_status::timeout){
        fn();
    }
}

template <typename Interval, typename Callback>
OneShotRunner<Interval, Callback>::OneShotRunner(){
    stopFuture = stopPromise.get_future();
}
