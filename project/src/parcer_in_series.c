#include "parcer_in_series.h"

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
    if (errno == ENOTTY) {
        errno = 0;
    }
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
            if (errno == ENOTTY) {
                errno = 0;
            }
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

int tone_counter(char* str, long int* result) {
    if (unlikely(!str)) {
        fprintf(stderr, "%s\n", "Error: input stream isn't exist");
        return -1;
    }

    long int tone = 0;
    do {
        str = strchr(str, ':');
        if (!str)
            break;

        if (*(str + 1) == ')') {
            tone++;
        }
        if (*(str + 1) == '(') {
            tone--;
        }
    } while (str++);
    *result = tone;

    return 0;
}

int main_workflow_malloc(FILE* is, long int* tone) {
    char* str = malloc_read(is);
    if (errno == ENOTTY) {
            errno = 0;
    }
    if (unlikely(!str)) {
        fprintf(stderr, "%s\n", "Error: main_workflow_malloc");
        return -1;
    }

    tone_counter(str, tone);

    free(str);

    return 0;
}

int main_workflow_mmap(FILE* is, long int* tone) {
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

    tone_counter(str, tone);

    munmap(str, statbuf.st_size);
    if (unlikely(error_handler("munmap"))) {
        return -1;
    }

    return 0;
}

int main_workflow(FILE* is, long int* tone) {
    if (unlikely(!is)) {
        fprintf(stderr, "%s\n", "Error: main_workflow_malloc");
        return -1;
    }

    if (is == stdin) {
        if (main_workflow_malloc(is, tone)) {
            fprintf(stderr, "%s\n", "Error: main_workflow_malloc");
            return -1;
        }
        return 0;
    }

    if (main_workflow_mmap(is, tone)) {
        fprintf(stderr, "%s\n", "Error: main_workflow_mmap");
        return -1;
    }
    return 0;
}
