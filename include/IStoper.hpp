#pragma once 

#include "types.hpp"


class IStoper{
public:
    virtual secondsDouble getElapsedTime() const = 0;
    virtual void start() = 0;
    virtual ~IStoper();
};

IStoper::~IStoper()
{
}
