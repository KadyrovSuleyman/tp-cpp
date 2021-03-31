 
#ifndef PROJECT_INCLUDE_PARCER_IN_PARALLEL_H_
#define PROJECT_INCLUDE_PARCER_IN_PARALLEL_H_

#include "parcer_in_series.h"

#include <stdatomic.h>
#include <pthread.h>

int pthread_main_workflow_malloc(FILE* is, long int* tone);

int pthread_main_workflow(FILE* is, long int* tone);
int pthread_main_workflow_mmap(FILE* is, long int* tone);
int pthread_main_workflow_malloc(FILE* is, long int* tone);

// #include <stdio.h>
// #include <errno.h>
// #include <stdlib.h>
// #include <string.h>

// #include <sys/types.h>
// #include <sys/stat.h>
// #include <unistd.h>
// #include <sys/mman.h>

// int error_handler(const char* invalid_func);
// int tone_counter(char* str, long int* result);
// char* malloc_read(FILE* is);
// int main_workflow_malloc(FILE* is, long int* tone);
// int main_workflow_mmap(FILE* is, long int* tone);
// int main_workflow(FILE* is, long int* tone);

#endif  // PROJECT_INCLUDE_PARCER_IN_PARALLEL_H_
