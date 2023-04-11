add_library(Exceptions IntervalLessThanZero.cpp)
target_include_directories(Exceptions PUBLIC ../include)

add_library(SimpleTimer SimpleTimer.cpp ITimer.cpp)
target_include_directories(SimpleTimer PUBLIC ../include)

add_library(Stoper Stoper.cpp IStoper.cpp)
target_include_directories(Stoper PUBLIC ../include)