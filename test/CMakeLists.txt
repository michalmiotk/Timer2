include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(test test.cpp)
target_include_directories(test PUBLIC ../include)
target_link_libraries(test GTest::gtest_main GTest::gmock_main)
include(GoogleTest)
gtest_discover_tests(test)

add_custom_command(TARGET test POST_BUILD COMMAND ./test)