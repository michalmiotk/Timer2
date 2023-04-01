#include <functional>
#include <chrono>
#include <condition_variable>

#include "IRunner.hpp"


template <typename T=secondsDouble>
class RecurrentRunner: public IRunner<T>{
public:
    void stop() override;
    void run(std::function<void()> fn, T timeToStart) override;
private:
    std::condition_variable cv;
};

template <typename T>
void RecurrentRunner<T>::stop(){
    cv.notify_one();
}

template <typename T>
void RecurrentRunner<T>::run(std::function<void()> fn, T interval){
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
