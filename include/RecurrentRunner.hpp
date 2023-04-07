#include <functional>
#include <chrono>
#include <future>

#include "IRunner.hpp"


template <typename Interval=std::chrono::milliseconds, typename Function=std::function<void()>, typename ... Args>
class RecurrentRunner: public IRunner<Interval, Function, Args...>{
public:
    void stop() override;
    void run(Function, Interval timeToStart, Args...) override;
    RecurrentRunner();
private:
    std::promise<void> stopPromise;
    std::future<void> stopFuture;
};

template <typename Interval , typename Function, typename ... Args>
void RecurrentRunner<Interval, Function, Args...>::stop(){
    stopPromise.set_value();
}

template <typename Interval , typename Function, typename ... Args>
void RecurrentRunner<Interval, Function, Args...>::run(Function fn, Interval interval, Args... args){
    while(true){
        if(stopFuture.wait_for(interval) == std::future_status::timeout)
        {
            fn(args...);
        }else{
            break;
        }
    }
}

template <typename Interval , typename Function, typename ... Args>
RecurrentRunner<Interval, Function, Args...>::RecurrentRunner(){
    stopFuture = stopPromise.get_future();
}
