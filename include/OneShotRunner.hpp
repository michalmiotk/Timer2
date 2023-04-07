#include <functional>
#include <chrono>
#include <future>

#include "IRunner.hpp"

template <typename Interval=std::chrono::milliseconds, typename Function=std::function<void()>, typename ... Args>
class OneShotRunner: public IRunner<Interval, Function, Args...>{
public:
    void stop() override; 
    void run(Function, Interval timeToStart, Args...) override;
    OneShotRunner();
private:
    std::promise<void> stopPromise;
    std::future<void> stopFuture;
};

template <typename Interval, typename Function, typename ... Args>
void OneShotRunner<Interval, Function, Args...>::stop(){
    stopPromise.set_value();
}

template <typename Interval, typename Function, typename ... Args>
void OneShotRunner<Interval, Function, Args...>::run(Function fn, Interval timeToStart, Args... args){
    if(stopFuture.wait_for(timeToStart) == std::future_status::timeout){
        fn(args...);
    }
}

template <typename Interval, typename Function, typename ... Args>
OneShotRunner<Interval, Function, Args...>::OneShotRunner(){
    stopFuture = stopPromise.get_future();
}
