cmake_minimum_required(VERSION 3.17)

project(test-runner)

include_directories("../wheels/include")
include_directories("../wheels/tests")

add_executable(test-runner)

target_sources(test-runner PRIVATE runner.cpp)

