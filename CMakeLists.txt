project(Timer)
cmake_minimum_required(VERSION 3.1)
set(CMAKE_POLICY_DEFAULT_CMP0079 NEW)
set(CMAKE_PROJECT_VERSION 1.0.0)
set(CMAKE_PROJECT_VERSION_MAJOR "")
set(CMAKE_PROJECT_VERSION_MINOR "")
set(CMAKE_PROJECT_VERSION_PATCH "")

add_compile_options(-Wall -Wextra -Wpedantic --std=c++23)

find_library(curses NAMES curses)

add_subdirectory(test)
add_subdirectory(src)

add_executable(main main.cpp)
target_link_libraries(main curses Stoper SimpleTimer)
target_include_directories(main PUBLIC include)
