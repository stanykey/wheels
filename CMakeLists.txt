cmake_minimum_required(VERSION 3.25)

project(wheels CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS OFF)

if(CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
    set(WHEELS_IS_TOP_LEVEL YES)
else()
    set(WHEELS_IS_TOP_LEVEL NO)
endif()

if(WHEELS_IS_TOP_LEVEL)
    set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE BOOL "Export compile_commands.json")
endif()

option(ENABLE_TESTING "Build tests" ${WHEELS_IS_TOP_LEVEL})
option(ENABLE_CLANG_TIDY "Enable static analysis with clang-tidy" ${WHEELS_IS_TOP_LEVEL})

if(ENABLE_CLANG_TIDY)
    find_program(CLANGTIDY clang-tidy)
    if(NOT CLANGTIDY)
        message(SEND_ERROR "clang-tidy requested but executable not found")
    endif()

    set(WHEELS_CLANG_TIDY_COMMAND ${CLANGTIDY} --extra-arg=-Wno-unknown-warning-option)

    if(NOT CMAKE_CXX_STANDARD STREQUAL "")
        if(CMAKE_CXX_CLANG_TIDY_DRIVER_MODE STREQUAL "cl")
            list(APPEND WHEELS_CLANG_TIDY_COMMAND --extra-arg=/std:c++${CMAKE_CXX_STANDARD})
        else()
            list(APPEND WHEELS_CLANG_TIDY_COMMAND --extra-arg=-std=c++${CMAKE_CXX_STANDARD})
        endif()
    endif()

    function(wheels_enable_clang_tidy target)
        set_property(TARGET ${target} PROPERTY CXX_CLANG_TIDY "${WHEELS_CLANG_TIDY_COMMAND}")
    endfunction()
else()
    function(wheels_enable_clang_tidy target)
    endfunction()
endif()

add_subdirectory(src)

if(ENABLE_TESTING)
    enable_testing()
    add_subdirectory(tests)
endif()
