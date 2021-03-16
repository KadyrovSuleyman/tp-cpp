INCLUDE_DIRECTORIES(include)
ADD_LIBRARY(matrix STATIC src/matrix.c)

ADD_SUBDIRECTORY(tests)
INCLUDE_DIRECTORIES(tests)

add_executable(main src/main.c)
target_link_libraries(main matrix)


set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/CMakeModules)
include(CodeCoverage)
append_coverage_compiler_flags()