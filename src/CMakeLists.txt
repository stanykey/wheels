# core library

set(header_files
    ${CMAKE_CURRENT_SOURCE_DIR}/wheels/helpers/fallback.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/wheels/helpers/variadic.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/wheels/helpers.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/wheels/random/random.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/wheels/random.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/wheels/string/constexpr.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/wheels/string/hash.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/wheels/string/trash.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/wheels/string.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/wheels/variant/overload.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/wheels/variant.hpp
)

add_library(wheels INTERFACE)

target_sources(wheels INTERFACE "$<BUILD_INTERFACE:${header_files}>")
target_include_directories(wheels INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/>)
target_include_directories(wheels SYSTEM INTERFACE $<INSTALL_INTERFACE:$<INSTALL_PREFIX>/include>)

add_library(wheels::wheels ALIAS wheels)
