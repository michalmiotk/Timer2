find_package(GTest)
include_directories(../src)

add_executable(testOneShotRunner testOneShotRunner.cpp)
target_include_directories(testOneShotRunner PUBLIC ../include)
target_link_libraries(testOneShotRunner GTest::gtest_main GTest::gmock_main OneShotRunner)

include(GoogleTest)


add_custom_command(TARGET testOneShotRunner POST_BUILD COMMAND ./testOneShotRunner)
