#ifndef PROJECT_INCLUDE_PARCER_H_
#define PROJECT_INCLUDE_PARCER_H_

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

char* readfile(FILE* f);

int error_handler(const char* invalid_func);
char* malloc_read(FILE* f);
char* mmap_read(FILE* f);

#endif  // PROJECT_INCLUDE_PARCER_H_