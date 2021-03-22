include_directories(include)
add_library(parcer STATIC src/parcer.c)

add_subdirectory(test)

include_directories(test)

add_executable(main src/main.c)
target_link_libraries(main parcer)