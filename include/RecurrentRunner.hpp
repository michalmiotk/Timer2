#include <functional>
#include <chrono>
#include <condition_variable>

#include "IRunner.hpp"


template <typename T=std::chrono::milliseconds>
class RecurrentRunner: public IRunner<T>{
public:
    void stop() override;
    void run(std::function<void()> fn, T timeToStart) override;
private:
    std::condition_variable cv;
    bool stopped{false};
};

template <typename T>
void RecurrentRunner<T>::stop(){
    stopped = true;
    cv.notify_all();
}

template <typename T>
void RecurrentRunner<T>::run(std::function<void()> fn, T interval){
     std::mutex m;
    std::unique_lock<std::mutex> l(m);
    while(not stopped){
        if(cv.wait_for(l, interval) == std::cv_status::timeout){
            fn();
        }else{
            break;
        }
    }
}
