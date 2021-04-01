include_directories(include)
add_library(parcer_in_series STATIC src/parcer_in_series.c)
add_library(parcer_in_parallel SHARED src/parcer_in_parallel.c)

add_subdirectory(test)

include_directories(test)

add_executable(main src/main.c)
target_link_libraries(main parcer_in_series)
target_link_libraries(main parcer_in_parallel)
target_link_libraries(main Threads::Threads)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/CMakeModules)
include(CodeCoverage)
append_coverage_compiler_flags()