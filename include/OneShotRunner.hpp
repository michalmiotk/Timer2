#include <functional>
#include <chrono>
#include <future>

#include "IRunner.hpp"


template <typename T=std::chrono::milliseconds>
class OneShotRunner: public IRunner<T>{
public:
    void stop() override;
    void run(std::function<void()> fn, T timeToStart) override;
    OneShotRunner();
private:
    std::promise<void> stopPromise;
    std::future<void> stopFuture;
};

template <typename T>
void OneShotRunner<T>::stop(){
    stopPromise.set_value();
}

template <typename T>
void OneShotRunner<T>::run(std::function<void()> fn, T timeToStart){
    if(stopFuture.wait_for(timeToStart) == std::future_status::timeout){
        fn();
    }
}

template <typename T>
OneShotRunner<T>::OneShotRunner(){
    stopFuture = stopPromise.get_future();
}
