include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(testTimer testTimer.cpp)
target_include_directories(testTimer PUBLIC ../include)
target_link_libraries(testTimer GTest::gtest_main GTest::gmock_main)

add_executable(testOneShotRunner testOneShotRunner.cpp)
target_include_directories(testOneShotRunner PUBLIC ../include)
target_link_libraries(testOneShotRunner GTest::gtest_main GTest::gmock_main)

include(GoogleTest)
gtest_discover_tests(testTimer)
#gtest_discover_tests(testOneShotRunner)

add_custom_command(TARGET testTimer POST_BUILD COMMAND ./testTimer)
add_custom_command(TARGET testOneShotRunner POST_BUILD COMMAND ./testOneShotRunner)