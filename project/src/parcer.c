#include "parcer.h"

#define unlikely(x)     __builtin_expect((x), 0)
#define START_STRING_LENGTH 5

int error_handler(const char* invalid_func) {
    if (unlikely(errno)) {
        perror(invalid_func);
        return -1;
    }

    return 0;
}


char* malloc_read(FILE* f) {
    size_t str_len = START_STRING_LENGTH;
    // char* result = (char*)malloc(sizeof(char) * str_len);
    char* result = (char*)calloc(sizeof(char), str_len);

    if (unlikely(error_handler("malloc"))) {
        free(result);
        return NULL;
    }

    char* carriage = result;
    size_t j = str_len;


    // realloc(result, 2 * str_len);

    // realloc(result, 4 * str_len);


    while (fscanf(f, "%c", carriage++) != EOF) {

        str_len++;
        reallocarray(result, sizeof(char), str_len);
        // if (unlikely(j-- == 1)) {
            // str_len *= 2;
        //     j = str_len;
            // if (unlikely(!reallocarray(result, sizeof(char), str_len))) {
            //     free(result);
            //     return NULL;
            // }

            // fprintf(stderr, "%s\n", "check");
        // }

        // fprintf(stdout, "%zu\n", j);
        fprintf(stdout, "%zu\n", strlen(result));
        // fprintf(stdout, "%s\n", result);
        // fprintf(stdout, "%zu\n", str_len);
    }

    // fprintf(stdout, "%zu\n", sizeof(result));
    fprintf(stdout, "%s\n", result);
    fprintf(stdout, "%zu\n", strlen(result));

    // fprintf(stdout, "%c\n", result_start[0]);
    // fprintf(stdout, "%c\n", result_start[1]);
    // fprintf(stdout, "%c\n", result_start[2]);
    // fprintf(stdout, "%c\n", result_start[3]);

    return result;

}

char* mmap_read(FILE* f) {

}

char* readfile(FILE* f) {
    if (unlikely(!f)) {
        fprintf(stderr, "%s\n", "input stream isn't exist");
        return NULL;
    }

    if (f == stdin) {
        char* result = malloc_read(f);
        if (unlikely(!result)) {
            fprintf(stderr, "%s\n", "Error: malloc_read");
            return NULL;
        }
        return result;
    }

    char* result = mmap_read(f);
    if  (unlikely(!result)) {
        fprintf(stderr, "%s\n", "Error: mmap_read");
        return NULL;
    }

    return result;
}
