cmake_minimum_required(VERSION 3.21)

# C++ settings
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS OFF)


# Toolchain must be set before defining project()
option(USE_VCPKG "Use Vcpkg as toolchain" YES)
if(USE_VCPKG AND NOT CMAKE_TOOLCHAIN_FILE)
    if(DEFINED ENV{VCPKG_ROOT})
        set(vcpkg "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")
        if(EXISTS vcpkg)
            set(CMAKE_TOOLCHAIN_FILE "${vcpkg}" CACHE FILEPATH "CMake toolchain file")
            message(STATUS "vcpkg toolchain found: ${CMAKE_TOOLCHAIN_FILE}")
            include($$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake)
        else()
            message(SEND_ERROR "vcpkg requested but VCPKG_ROOT isn't set")
        endif()
    endif ()
endif()

message(STATUS "Toolchain found: ${CMAKE_TOOLCHAIN_FILE}")


# Project configuration
project(wheels CXX)

add_subdirectory(src)

# Testing
option(ENABLE_TESTING "Enable Test Builds" YES)
if(ENABLE_TESTING)
    enable_testing()
    add_subdirectory(tests)
endif()

# Static analysis (better to place at the end when all targets already defined)
option(ENABLE_CLANG_TIDY "Enable static analysis with clang-tidy" YES)
if(ENABLE_CLANG_TIDY)
    find_program(CLANGTIDY clang-tidy)
    if(CLANGTIDY)
        set(CMAKE_CXX_CLANG_TIDY ${CLANGTIDY} -extra-arg=-Wno-unknown-warning-option)

        # set C++ standard
        if(NOT CMAKE_CXX_STANDARD STREQUAL "")
            if(CMAKE_CXX_CLANG_TIDY_DRIVER_MODE STREQUAL "cl")
                set(CMAKE_CXX_CLANG_TIDY ${CMAKE_CXX_CLANG_TIDY} --extra-arg=/std:c++${CMAKE_CXX_STANDARD})
            else()
                set(CMAKE_CXX_CLANG_TIDY ${CMAKE_CXX_CLANG_TIDY} --extra-arg=-std=c++${CMAKE_CXX_STANDARD})
            endif()
        endif()
    else()
        message(SEND_ERROR "clang-tidy requested but executable not found")
    endif()
endif()
