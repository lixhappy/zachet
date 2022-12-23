cmake_minimum_required(VERSION 3.14)
project(zachet)

set(CMAKE_CXX_STANDARD 14)

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

set(TESTS
    tests/test.cpp
)

set(SORTS
    tests/quick_sort.hpp
    tests/quick_sort.cpp
)

set(MATRIX
    matrix/matrix.hpp
    matrix/matrix.cpp
)

set(POLY
    polynomial/poly.hpp
    polynomial/poly.cpp
)


add_executable(
    tests
    ${TESTS}
    ${SORTS}
    ${MATRIX}
    ${POLY}
)

target_link_libraries(
    tests
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(tests)
