#include <functional>
#include <chrono>
#include <future>

#include "IRunner.hpp"
#include "IntervalLessThanZero.hpp"

template <typename Interval=std::chrono::milliseconds, typename Callback=std::function<void()>>
class RecurrentRunner: public IRunner<Interval, Callback>{
public:
    void stop() override;
    void run(Callback&&, Interval timeToStart) override;
    RecurrentRunner();
private:
    std::promise<void> stopPromise;
    std::future<void> stopFuture;
};

template <typename Interval , typename Callback>
void RecurrentRunner<Interval, Callback>::stop(){
    stopPromise.set_value();
}

template <typename Interval , typename Callback>
void RecurrentRunner<Interval, Callback>::run(Callback&& fn, Interval interval){
    if(interval.count()<0){
        throw IntervalLessThanZero{};
    }

    while(true){
        if(stopFuture.wait_for(interval) == std::future_status::timeout)
        {
            fn();
        }else{
            break;
        }
    }
}

template <typename Interval , typename Callback>
RecurrentRunner<Interval, Callback>::RecurrentRunner(){
    stopFuture = stopPromise.get_future();
}
