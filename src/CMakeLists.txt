get_filename_component(include_dir ${CMAKE_CURRENT_SOURCE_DIR}/wheels ABSOLUTE)

set(header_files
    ${include_dir}/bits.hpp
    ${include_dir}/bits/operations.hpp

    ${include_dir}/helpers.hpp
    ${include_dir}/helpers/fallback.hpp
    ${include_dir}/helpers/variadic.hpp

    ${include_dir}/random.hpp
    ${include_dir}/random/random.hpp

    ${include_dir}/string.hpp
    ${include_dir}/string/constexpr.hpp
    ${include_dir}/string/hash.hpp
    ${include_dir}/string/trash.hpp

    ${include_dir}/variant.hpp
    ${include_dir}/variant/overload.hpp
)

# Base target for common options.
add_library(wheels_base INTERFACE)
target_sources(wheels_base INTERFACE ${header_files})

# Core library.
add_library(wheels_core INTERFACE)
add_library(wheels::core ALIAS wheels_core)
target_link_libraries(wheels_core INTERFACE wheels_base)
target_include_directories(wheels_core SYSTEM INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

# Core library with warnings; for development only.
add_library(wheels_dev INTERFACE)
add_library(wheels::dev ALIAS wheels_dev)
target_link_libraries(wheels_dev INTERFACE wheels_base)
target_include_directories(wheels_dev INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
if(MSVC)
    # "default" warnings
    target_compile_options(wheels_dev INTERFACE
        /W4     # Baseline reasonable warnings
        /w14242 # 'identifier': conversion from 'type1' to 'type1', possible loss of data
        /w14254 # 'operator': conversion from 'type1:field_bits' to 'type2:field_bits', possible loss of data
        /w14263 # 'function': member function does not override any base class virtual member function
        /w14265 # 'classname': class has virtual functions, but destructor is not virtual instances of this class may not
        /w14287 # 'operator': unsigned/negative constant mismatch
        /we4289 # nonstandard extension used: 'variable': loop control variable declared in the for-loop is used outside
        /w14296 # 'operator': expression is always 'boolean_value'
        /w14311 # 'variable': pointer truncation from 'type1' to 'type2'
        /w14545 # expression before comma evaluates to a function which is missing an argument list
        /w14546 # function call before comma missing argument list
        /w14547 # 'operator': operator before comma has no effect; expected operator with side-effect
        /w14549 # 'operator': operator before comma has no effect; did you intend 'operator'?
        /w14555 # expression has no effect; expected expression with side- effect
        /w14619 # pragma warning: there is no warning number 'number'
        /w14640 # Enable warning on thread un-safe static member initialization
        /w14826 # Conversion from 'type1' to 'type_2' is sign-extended. This may cause unexpected runtime behavior.
        /w14905 # wide string literal cast to 'LPSTR'
        /w14906 # string literal cast to 'LPWSTR'
        /w14928 # illegal copy-initialization; more than one user-defined conversion has been implicitly applied
    )

    # standards conformance mode for MSVC compiler
    target_compile_options(wheels_dev INTERFACE /permissive-)

    # turn off CRT warnings
    # target_compile_options(wheels_dev INTERFACE /D _CRT_SECURE_NO_WARNINGS)

    # warnings are treated as errors
    target_compile_options(wheels_dev INTERFACE /WX)
else()
    # "default" warnings
    target_compile_options(wheels_dev INTERFACE
        -Wall -Wextra      # reasonable and standard
        -Wshadow           # warn the user if a variable declaration shadows one from a parent context
        -Wnon-virtual-dtor # warn the user if a class with virtual functions has a non-virtual destructor. This helps
    )

    # catch hard to track down memory errors
    target_compile_options(wheels_dev INTERFACE
        -Wold-style-cast       # warn for c-style casts
        -Wcast-align           # warn for potential performance problem casts
        -Wunused               # warn on anything being unused
        -Woverloaded-virtual   # warn if you overload (not override) a virtual function
        -Wpedantic             # warn if non-standard C++ is used
        -Wconversion           # warn on type conversions that may lose data
        -Wsign-conversion      # warn on sign conversions
        -Wnull-dereference     # warn if a null dereference is detected
        -Wdouble-promotion     # warn if float is implicit promoted to double
        -Wformat=2             # warn on security issues around functions that format output (ie printf)
        -Wimplicit-fallthrough # warn on statements that fallthrough without an explicit annotation
    )

    # some extends for GNU
    if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        target_compile_options(wheels_dev INTERFACE
            -Wmisleading-indentation # warn if indentation implies blocks where blocks do not exist
            -Wduplicated-cond        # warn if if / else chain has duplicated conditions
            -Wduplicated-branches    # warn if if / else branches have duplicated code
            -Wlogical-op             # warn about logical operations being used where bitwise were probably wanted
            -Wuseless-cast           # warn if you perform a cast to the same type
        )
    endif()

    # warnings are treated as errors
    target_compile_options(wheels_dev INTERFACE -Werror)
endif()

if(${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
    # MSVC requests to capture const(expr) variables in any case
    target_compile_options(wheels_dev INTERFACE -Wno-unused-lambda-capture)
endif()

# Umbrella target with all components.
add_library(wheels INTERFACE)
add_library(wheels::wheels ALIAS wheels)
target_link_libraries(wheels INTERFACE wheels::core)
