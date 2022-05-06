cmake_minimum_required(VERSION 3.17)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


option(USE_VCPKG "Use Vcpkg as toolchain" YES)
if (USE_VCPKG)
    if (DEFINED ENV{VCPKG_ROOT})
        include($ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake)
    else()
        message(SEND_ERROR "vcpkg requested but VCPKG_ROOT isn't set")
    endif()
endif()


option(ENABLE_CLANG_TIDY "Enable static analysis with clang-tidy" YES)
if (ENABLE_CLANG_TIDY)
    find_program(CLANGTIDY clang-tidy)
    if (CLANGTIDY)
        set(CMAKE_CXX_CLANG_TIDY ${CLANGTIDY} -extra-arg=-Wno-unknown-warning-option)
    else()
        message(SEND_ERROR "clang-tidy requested but executable not found")
    endif()
endif()


project(wheels)

add_subdirectory(src)

option(ENABLE_TESTING "Enable Test Builds" ON)
if (ENABLE_TESTING)
    add_subdirectory(tests)
endif()
