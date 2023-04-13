#pragma once

#include <exception>


class IntervalLessThanZero: public std::exception{
    const char * what();
};
