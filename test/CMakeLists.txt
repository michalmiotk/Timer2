find_package(GTest)
include_directories(../src)


add_executable(testTimer testTimer.cpp)
target_include_directories(testTimer PUBLIC ../include)
target_link_libraries(testTimer GTest::gtest_main GTest::gmock_main SimpleTimer Stoper)

add_executable(testOneShotRunner testOneShotRunner.cpp)
target_include_directories(testOneShotRunner PUBLIC ../include)
target_link_libraries(testOneShotRunner GTest::gtest_main GTest::gmock_main)

add_executable(testRecurrentRunner testRecurrentRunner.cpp)
target_include_directories(testRecurrentRunner PUBLIC ../include)
target_link_libraries(testRecurrentRunner GTest::gtest_main GTest::gmock_main)

include(GoogleTest)
gtest_discover_tests(testTimer)

add_custom_command(TARGET testTimer POST_BUILD COMMAND ./testTimer)
add_custom_command(TARGET testOneShotRunner POST_BUILD COMMAND ./testOneShotRunner)
add_custom_command(TARGET testRecurrentRunner POST_BUILD COMMAND ./testRecurrentRunner)