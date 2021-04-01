#ifndef PROJECT_INCLUDE_PARCER_IN_PARALLEL_H_
#define PROJECT_INCLUDE_PARCER_IN_PARALLEL_H_

#include <stdatomic.h>
#include <pthread.h>

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/mman.h>

int error_handler(const char* invalid_func);
void* pthread_tone_counter(void* _arg);
int threads_exec(char* str, long int* tone);
char* malloc_read(FILE* is);
int pthread_main_workflow_malloc(FILE* is, long int* tone);
int pthread_main_workflow_mmap(FILE* is, long int* tone);
int pthread_main_workflow(FILE* is, long int* tone);
int get_num_cores();

typedef struct {
    char* str;
    size_t str_len;
    long int result;
} Arg;



#endif  // PROJECT_INCLUDE_PARCER_IN_PARALLEL_H_
