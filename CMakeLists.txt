cmake_minimum_required(VERSION 3.17)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


project(wheels)

add_subdirectory(src)

option(ENABLE_TESTING "Enable Test Builds" OFF)
if (ENABLE_TESTING)
    add_subdirectory(tests)
endif()
