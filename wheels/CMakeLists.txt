cmake_minimum_required(VERSION 3.17)

project(wheels)

add_library(wheels INTERFACE)

target_include_directories(wheels
    INTERFACE
        include/
)

target_sources(wheels
    INTERFACE
        include/wheels/helpers/fallback.hpp
        include/wheels/helpers/variadic.hpp
        include/wheels/helpers.hpp
        include/wheels/random/random.hpp
        include/wheels/random.hpp
        include/wheels/string/constexpr.hpp
        include/wheels/string/hash.hpp
        include/wheels/string/trash.hpp
        include/wheels/string.hpp
        include/wheels/variant/overload.hpp
        include/wheels/variant.hpp
)
