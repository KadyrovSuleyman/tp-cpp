#ifndef PROJECT_INCLUDE_PARCER_H_
#define PROJECT_INCLUDE_PARCER_H_

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/mman.h>


char* readfile(FILE* is);

int error_handler(const char* invalid_func);
char* malloc_read(FILE* is);
char* mmap_read(FILE* is);

int main_workflow_mmap(FILE* is);

#endif  // PROJECT_INCLUDE_PARCER_H_