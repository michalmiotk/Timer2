project(x)
cmake_minimum_required(VERSION 3.1)
set(CMAKE_CXX_COMPILER g++)
add_compile_options(-Wall -Wextra -Wpedantic --std=c++20)

find_library(curses NAMES curses)

add_executable(main main.cpp)
target_link_libraries(main curses)
target_include_directories(main PUBLIC include)