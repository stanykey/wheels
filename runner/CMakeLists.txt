cmake_minimum_required(VERSION "3.17")

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories("../")
add_executable(runner runner.cpp)
