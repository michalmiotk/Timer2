#include <functional>
#include <chrono>
#include <condition_variable>

#include "IRunner.hpp"


template <typename T=secondsDouble>
struct RecurrentRunner:  IRunner<T>{
    std::condition_variable cv;
    
    void stop() override{
        cv.notify_one();
    }

    void run(std::function<void()> fn, T interval){
        std::mutex m;
        std::unique_lock<std::mutex> l(m);
        bool stopped = false;
        while(not stopped){
            if(cv.wait_for(l, interval) == std::cv_status::timeout){
                fn();
            }else{
                std::cout<<"somebody pressed stop"<<std::endl;
                stopped = true;
            }
        }
    }
};