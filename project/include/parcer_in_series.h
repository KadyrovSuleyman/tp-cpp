#ifndef PROJECT_INCLUDE_PARCER_IN_SERIES_H_
#define PROJECT_INCLUDE_PARCER_IN_SERIES_H_

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/mman.h>

int error_handler(const char* invalid_func);
int tone_counter(char* str, long int* result);
char* malloc_read(FILE* is);
int main_workflow_malloc(FILE* is, long int* tone);
int main_workflow_mmap(FILE* is, long int* tone);
int main_workflow(FILE* is, long int* tone);

#endif  // PROJECT_INCLUDE_PARCER_IN_SERIES_H_
