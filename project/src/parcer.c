#include "parcer.h"

#define unlikely(x)     __builtin_expect((x), 0)
#define START_STRING_LENGTH 16
#define CHANK_LENGTH 16

int error_handler(const char* invalid_func) {
    if (unlikely(errno)) {
        perror(invalid_func);
        return -1;
    }
    return 0;
}


char* malloc_read(FILE* f) {
    size_t str_len = START_STRING_LENGTH;
    char* result = (char*)malloc(sizeof(char) * str_len);
    if (unlikely(error_handler("malloc"))) {
        free(result);
        return NULL;
    }

    char* carriage = result;
    size_t i = 0;
    size_t j = 1;
    while (!feof(f)) {
        if (i++ == j) {
            str_len <<= 1;
            j <<= 1;

            result = (char*)realloc(result, sizeof(char) * str_len);
            if (unlikely(error_handler("realloc"))) {
                free(result);
                return NULL;
            }
            carriage = result + (str_len >> 1);
        }

        size_t t = fread(carriage, sizeof(char), CHANK_LENGTH, f);
        carriage += t;
    }
    *carriage = '\0';

    result = (char*)realloc(result, sizeof(char) * (strlen(result) + 1));
    if (unlikely(error_handler("realloc"))) {
        free(result);
        return NULL;
    }

    return result;
}

char* mmap_read(FILE* f) {
    struct stat statbuf;
    int fd = fileno(f);
    if (unlikely(error_handler("fileno"))) {
        return NULL;
    }

    fstat(fd, &statbuf);
    if (unlikely(error_handler("fstat"))) {
        return NULL;
    }

    char* result = mmap(NULL, statbuf.st_size, PROT_READ, MAP_SHARED, fd, 0);
    if (unlikely(error_handler("fstat"))) {
        munmap(result, statbuf.st_size);
        return NULL;
    }    

    return result;

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
