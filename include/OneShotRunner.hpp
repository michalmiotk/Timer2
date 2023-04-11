#include <functional>
#include <chrono>
#include <future>
#include <cassert>

#include "IRunner.hpp"
#include "IntervalLessThanZero.hpp"


template <typename Interval=std::chrono::milliseconds, typename Callback=std::function<void()>, typename ... Args>
class OneShotRunner: public IRunner<Interval, Callback, Args...>{
public:
    void stop() override; 
    void run(Callback&&, Interval timeToStart, Args&&...) override;
    OneShotRunner();
private:
    std::promise<void> stopPromise;
    std::future<void> stopFuture;
};

template <typename Interval, typename Callback, typename ... Args>
void OneShotRunner<Interval, Callback, Args...>::stop(){
    stopPromise.set_value();
}

template <typename Interval, typename Callback, typename ... Args>
void OneShotRunner<Interval, Callback, Args...>::run(Callback&& fn, Interval timeToStart, Args&&... args){
    if(timeToStart.count()<0){
        throw IntervalLessThanZero{};
    }
    if(stopFuture.wait_for(timeToStart) == std::future_status::timeout){
        fn(std::forward<Args>(args)...);
    }
}

template <typename Interval, typename Callback, typename ... Args>
OneShotRunner<Interval, Callback, Args...>::OneShotRunner(){
    stopFuture = stopPromise.get_future();
}
