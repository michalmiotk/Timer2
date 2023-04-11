#include <functional>
#include <chrono>
#include <future>

#include "IRunner.hpp"
#include "IntervalLessThanZero.hpp"

template <typename Interval=std::chrono::milliseconds, typename Callback=std::function<void()>, typename ... Args>
class RecurrentRunner: public IRunner<Interval, Callback, Args...>{
public:
    void stop() override;
    void run(Callback&&, Interval timeToStart, Args&&...) override;
    RecurrentRunner();
private:
    std::promise<void> stopPromise;
    std::future<void> stopFuture;
};

template <typename Interval , typename Callback, typename ... Args>
void RecurrentRunner<Interval, Callback, Args...>::stop(){
    stopPromise.set_value();
}

template <typename Interval , typename Callback, typename ... Args>
void RecurrentRunner<Interval, Callback, Args...>::run(Callback&& fn, Interval interval, Args&&... args){
    if(interval.count()<0){
        throw IntervalLessThanZero{};
    }

    while(true){
        if(stopFuture.wait_for(interval) == std::future_status::timeout)
        {
            fn(std::forward<Args>(args)...);
        }else{
            break;
        }
    }
}

template <typename Interval , typename Callback, typename ... Args>
RecurrentRunner<Interval, Callback, Args...>::RecurrentRunner(){
    stopFuture = stopPromise.get_future();
}
