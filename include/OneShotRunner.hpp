#include <functional>
#include <chrono>
#include <condition_variable>

#include "IRunner.hpp"


template <typename T=std::chrono::milliseconds>
class OneShotRunner: public IRunner<T>{
public:
    void stop() override;
    void run(std::function<void()> fn, T timeToStart) override;
private:
    std::condition_variable cv;
};

template <typename T>
void OneShotRunner<T>::stop(){
    cv.notify_one();
}

template <typename T>
void OneShotRunner<T>::run(std::function<void()> fn, T timeToStart){
    std::mutex m;
    std::unique_lock<std::mutex> l(m);
    auto status = cv.wait_for(l, timeToStart);
    if(status == std::cv_status::timeout){
        fn();
    }else{
        if(status == std::cv_status::no_timeout)
        {
            std::cout<<"somebody asked stop"<<std::endl;
        }
    }
}
