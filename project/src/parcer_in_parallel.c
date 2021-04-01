#include "parcer_in_parallel.h"

#define unlikely(x)     __builtin_expect((x), 0)
#define START_STRING_LENGTH 16
#define CHANK_LENGTH 16


#ifdef _WIN32
#include <windows.h>
#elif MACOS
#include <sys/param.h>
#include <sys/sysctl.h>
#else
#include <unistd.h>
#endif

int get_num_cores() {
#ifdef WIN32
    SYSTEM_INFO sysinfo;
    GetSystemInfo(&sysinfo);
    return sysinfo.dwNumberOfProcessors;
#elif MACOS
    int nm[2];
    size_t len = 4;
    uint32_t count;

    nm[0] = CTL_HW; nm[1] = HW_AVAILCPU;
    sysctl(nm, 2, &count, &len, NULL, 0);

    if (count < 1) {
        nm[1] = HW_NCPU;
        sysctl(nm, 2, &count, &len, NULL, 0);
        if (count < 1) { count = 1; }
    }
    return count;
#else
    return sysconf(_SC_NPROCESSORS_ONLN);
#endif
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

int error_handler(const char* invalid_func) {
    if (unlikely(errno)) {
        perror(invalid_func);
        return -1;
    }
    return 0;
}

void* pthread_tone_counter(void* _arg) {
    Arg* arg = (Arg*)_arg;
    char* str = arg->str;
    size_t str_len = arg->str_len;
    long int result = arg->result;

    if (unlikely(!str)) {
        fprintf(stderr, "%s\n", "Error: input stream isn't exist");
        return NULL;
        // return -1;
    }

    char* str_start = str;
    long int tone = 0;
    do {
        str = strchr(str, ':');
        if (!str || ((str - str_start) >= str_len)) {
            break;
        }
        if (*(str + 1) == ')') {
            tone++;
        }
        if (*(str + 1) == '(') {
            tone--;
        }
    } while (str++);

    result = tone;
    arg->str = str;
    arg->str_len = str_len;
    arg->result = result;

    return NULL;
}

int threads_exec(char* str, long int* tone) {
    int num_cores = get_num_cores();
    size_t pth_str_len = strlen(str) / num_cores;

    pthread_t* thread = (pthread_t*)malloc(sizeof(pthread_t) * num_cores);
    int* error = (int*)malloc(sizeof(int) * num_cores);
    Arg* args = (Arg*)malloc(sizeof(Arg) * num_cores);

    for (size_t i = 0; i < num_cores; ++i) {
        args[i].str = str + (i * pth_str_len);
        args[i].str_len = pth_str_len;
        args[i].result = 0;
    }
    args[num_cores - 1].str_len = strlen(str) - (3 * pth_str_len);

    for (size_t i = 1; i < num_cores; ++i) {
        if (*(args[i].str - 1) == ':') {
            if (*(args[i].str) == ')') {
                *tone++;
            }
            if (*(args[i].str) == '(') {
                *tone--;
            }            
        }
    }

    for (size_t i = 0; i < num_cores; ++i) {
        error[i] = pthread_create(&thread[i], NULL, pthread_tone_counter, (void*)&args[i]);
        if (error[i]) {
            fprintf(stderr, "%s\n", "Error: pthread_create");
            free(thread);
            free(error);
            free(args);
            return -1;
        }
    }

    for (size_t i = 0; i < num_cores; ++i) {
        pthread_join(thread[i], NULL);
        *tone += args[i].result;
    }

    free(thread);
    free(error);
    free(args);

    return 0;
}

int pthread_main_workflow_malloc(FILE* is, long int* tone) {
    char* str = malloc_read(is);
    if (errno == ENOTTY) {
        errno = 0;
    }
    if (unlikely(!str)) {
        fprintf(stderr, "%s\n", "Error: main_workflow_malloc");
        return -1;
    }
    threads_exec(str, tone);
    free(str);
    return 0;
}

int pthread_main_workflow_mmap(FILE* is, long int* tone) {
    struct stat statbuf;
    int fd = fileno(is);
    if (errno == ENOTTY) {
        errno = 0;
    }
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

    threads_exec(str, tone);

    munmap(str, statbuf.st_size);
    if (unlikely(error_handler("munmap"))) {
        return -1;
    }

    return 0;
}

int pthread_main_workflow(FILE* is, long int* tone) {
    if (unlikely(!is)) {
        fprintf(stderr, "%s\n", "Error: pthread_parcer_workflow");
        return -1;
    }

    if (is == stdin) {
        if (pthread_main_workflow_malloc(is, tone)) {
            fprintf(stderr, "%s\n", "Error: main_workflow_malloc");
            return -1;
        }
        return 0;
    }

    if (pthread_main_workflow_mmap(is, tone)) {
        fprintf(stderr, "%s\n", "Error: main_workflow_mmap");
        return -1;
    }
    return 0;
}
