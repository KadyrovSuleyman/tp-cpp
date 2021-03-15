cmake_minimum_required(VERSION 3.16)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

add_executable(mytest src/test.cpp)
target_link_libraries(mytest matrix)


enable_testing()

target_link_libraries(mytest matrix)

include_directories(gtest)
target_link_libraries(mytest gtest -lpthread)