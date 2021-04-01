cmake_minimum_required(VERSION 3.16)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

add_executable(mytest src/test.cpp)
target_link_libraries(mytest parcer_in_series)
target_link_libraries(mytest parcer_in_parallel)
target_link_libraries(mytest Threads::Threads)

enable_testing()

#include_directories(gtest)
target_link_libraries(mytest gtest -lpthread)