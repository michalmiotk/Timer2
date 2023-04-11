add_library(Exceptions IntervalLessThanZero.cpp)
target_include_directories(Exceptions PUBLIC ../include)

add_library(Timer Timer.cpp ITimer.cpp)
target_include_directories(Timer PUBLIC ../include)

add_library(Stoper Stoper.cpp IStoper.cpp)
target_include_directories(Stoper PUBLIC ../include)