cmake_minimum_required(VERSION 3.16)
project(parcer)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_THREAD_PREFER_PTHREAD ON)
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)        

set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -std=c++0x -Wall -Werror -Wextra -Wpedantic -ggdb3 -pthread")

add_subdirectory(project)

enable_testing()

include_directories(googletest)
# target_link_libraries(mytest gtest -lpthread)

add_subdirectory(googletest)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/CMakeModules)
if(CMAKE_COMPILER_IS_GNUCXX)
    include(CodeCoverage)
    append_coverage_compiler_flags()
endif()