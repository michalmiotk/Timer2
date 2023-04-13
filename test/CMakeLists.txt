find_package(GTest)
include_directories(../src)

include(GoogleTest)

add_executable(testSimpleTimer testSimpleTimer.cpp)
target_include_directories(testSimpleTimer PUBLIC ../include)
target_link_libraries(testSimpleTimer GTest::gtest_main GTest::gmock_main SimpleTimer Stoper)

gtest_discover_tests(testSimpleTimer)
