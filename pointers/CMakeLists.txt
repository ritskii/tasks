cmake_minimum_required(VERSION 3.28)
project(pointers)

add_executable(pointers main.cpp
        List.hpp)

include(FetchContent)

FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/release-1.12.1.zip
)

FetchContent_MakeAvailable(googletest)

add_executable(tests test.cpp)
target_link_libraries(tests gtest gtest_main)
enable_testing()