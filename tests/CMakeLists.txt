find_package(Catch2 CONFIG REQUIRED)

include(Catch)

add_library(wheels_test_base INTERFACE)
target_link_libraries(wheels_test_base INTERFACE
    Catch2::Catch2
    Catch2::Catch2WithMain
    wheels::dev
)

function(register_tests executable test_prefix)
    target_link_libraries(${executable} PRIVATE wheels_test_base)

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
