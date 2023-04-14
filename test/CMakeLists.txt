include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
include_directories(../src)

include(GoogleTest)

add_executable(testSimpleTimer testSimpleTimer.cpp)
target_include_directories(testSimpleTimer PUBLIC ../include)
target_link_libraries(testSimpleTimer GTest::gtest_main GTest::gmock_main SimpleTimer Stoper)

gtest_discover_tests(testSimpleTimer)
