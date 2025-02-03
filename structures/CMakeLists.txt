cmake_minimum_required(VERSION 3.28)
project(structures)

set(CMAKE_CXX_STANDARD 17)

add_executable(structures main.cpp
        AnyType.hpp
        AnyType.cpp)

include(FetchContent)

FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/release-1.12.1.zip
)

FetchContent_MakeAvailable(googletest)

add_executable(tests test.cpp)
target_link_libraries(tests gtest gtest_main)
enable_testing()