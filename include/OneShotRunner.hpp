#include <functional>
#include <chrono>
#include <condition_variable>

#include "IRunner.hpp"


template <typename T=secondsDouble>
struct OneShotRunner:  IRunner<T>{
    std::condition_variable cv;
    
    void stop() override{
        cv.notify_one();
    }

    void run(std::function<void()> fn, T timeToStart){
        std::mutex m;
        std::unique_lock<std::mutex> l(m);
        auto status = cv.wait_for(l, timeToStart);
        if(status == std::cv_status::timeout){
            fn();
        }else{
            if(status == std::cv_status::no_timeout)
            {
                std::cout<<"somebody pressed stop"<<std::endl;
            }
        }
    }
};