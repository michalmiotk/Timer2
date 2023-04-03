#pragma once 

#include "types.hpp"


template <typename T=secondsDouble>
class IStoper{
public:
    virtual T getElapsedTime() const = 0;
    virtual void start() = 0;
    virtual ~IStoper();
};

template <typename T>
IStoper<T>::~IStoper()
{
}
