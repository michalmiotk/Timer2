#include <functional>
#include <chrono>
#include <future>

#include "IRunner.hpp"


template <typename T=std::chrono::milliseconds>
class RecurrentRunner: public IRunner<T>{
public:
    void stop() override;
    void run(std::function<void()> fn, T timeToStart) override;
    RecurrentRunner();
private:
    std::promise<void> stopPromise;
    std::future<void> stopFuture;
};

template <typename T>
void RecurrentRunner<T>::stop(){
    stopPromise.set_value();
}

template <typename T>
void RecurrentRunner<T>::run(std::function<void()> fn, T interval){
    while(true){
        if(stopFuture.wait_for(interval) == std::future_status::timeout)
        {
            fn();
        }else{
            break;
        }
    }
}

template <typename T>
RecurrentRunner<T>::RecurrentRunner(){
    stopFuture = stopPromise.get_future();
}