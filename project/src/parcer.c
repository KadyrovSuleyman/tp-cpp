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


char* malloc_read(FILE* is) {
    size_t str_len = START_STRING_LENGTH;
    char* result = (char*)malloc(sizeof(char) * str_len);
    if (unlikely(error_handler("malloc"))) {
        free(result);
        return NULL;
    }

    char* carriage = result;
    size_t i = 0;
    size_t j = 1;
    while (!feof(is)) {
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

        size_t t = fread(carriage, sizeof(char), CHANK_LENGTH, is);
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

/*

char* mmap_read(FILE* is) {
    struct stat statbuf;
    int fd = fileno(is);
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

char* readfile(FILE* is) {
    if (unlikely(!is)) {
        fprintf(stderr, "%s\n", "input stream isn't exist");
        return NULL;
    }

    if (is == stdin) {
        char* result = malloc_read(is);
        if (unlikely(!result)) {
            fprintf(stderr, "%s\n", "Error: malloc_read");
            return NULL;
        }
        return result;
    }

    char* result = mmap_read(is);
    if  (unlikely(!result)) {
        fprintf(stderr, "%s\n", "Error: mmap_read");
        return NULL;
    }

    return result;
}

*/

int do_smth(char* str, long int* result) {
    if (unlikely(!str)) {
        fprintf(stderr, "%s\n", "Error: input stream isn't exist");
        return -1;
    }

    long int tone = 0;

    do {
        // if (*(str + 1) == ')') {
        //     tone++;
        // }
        // if (*(str + 1) == '(') {
        //     tone--;
        // }
        str = strchr(str, ':');
        fprintf(stdout, "%s\n", str);
    } while (str++);

    *result = tone;

    fprintf(stdout, "%ld\n", *result);

    return 0;
}

int main_workflow_malloc(FILE* is) {
    char* str = malloc_read(is);
    if (unlikely(!str)) {
        fprintf(stderr, "%s\n", "Error: main_workflow_malloc");
        return -1;
    }

    long int tone;
    do_smth(str, &tone);

    free(str);

    return 0;
}

int main_workflow_mmap(FILE* is) {
    struct stat statbuf;
    int fd = fileno(is);
    if (unlikely(error_handler("fileno"))) {
        return -1;
    }

    fstat(fd, &statbuf);
    if (unlikely(error_handler("fstat"))) {
        return -1;
    }

    char* str = mmap(NULL, statbuf.st_size, PROT_READ, MAP_SHARED, fd, 0);
    if (unlikely(error_handler("fstat"))) {
        munmap(str, statbuf.st_size);
        return -1;
    }

    long int tone;
    do_smth(str, &tone);

    munmap(str, statbuf.st_size);
    if (unlikely(error_handler("munmap"))) {
        return -1;
    }

    return 0;
}