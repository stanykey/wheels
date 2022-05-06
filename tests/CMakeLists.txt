find_package(Catch2 CONFIG REQUIRED)

include(Catch)

add_library(catch_main STATIC catch_main.cpp)
target_link_libraries(catch_main
    PUBLIC
        Catch2::Catch2
)

function(register_tests executable test_prefix)
    target_link_libraries(${executable} PRIVATE catch_main)

    catch_discover_tests(
        ${executable}
            TEST_PREFIX ${test_prefix}.
            EXTRA_ARGS -s --reporter=compact
    )
endfunction()

add_executable(tests tests.cpp)
add_executable(constexpr_tests constexpr_tests.cpp)
add_executable(relaxed_constexpr_tests constexpr_tests.cpp)
target_compile_definitions(relaxed_constexpr_tests PRIVATE -DCATCH_CONFIG_RUNTIME_STATIC_REQUIRE)

register_tests(tests "unittests")
register_tests(constexpr_tests "constexpr")
register_tests(relaxed_constexpr_tests "relaxed_constexpr")
