add_library(Exceptions IntervalLessThanZero.cpp)
target_include_directories(Exceptions PUBLIC ../include)

add_library(Stoper Stoper.cpp)
target_include_directories(Stoper PUBLIC ../include)

add_library(SimpleTimer SimpleTimer.cpp)
target_include_directories(SimpleTimer PUBLIC ../include)