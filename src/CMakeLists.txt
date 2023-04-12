add_library(Exceptions IntervalLessThanZero.cpp)
target_include_directories(Exceptions PUBLIC ../include)

add_library(Stoper Stoper.cpp IStoper.cpp)
target_include_directories(Stoper PUBLIC ../include)

add_library(OneShotRunner OneShotRunner.cpp IRunner.cpp)
target_include_directories(OneShotRunner PUBLIC ../include)