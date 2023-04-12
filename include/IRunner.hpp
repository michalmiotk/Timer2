#pragma once 

#include <functional>

#include "types.hpp"



class IRunner{
public:
    virtual void stop() = 0;
    virtual void run(std::function<void()>&&, milliseconds timeToStart) = 0;
    virtual ~IRunner();
};
