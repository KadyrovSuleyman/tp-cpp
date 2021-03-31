#include "parcer_in_series.h"
#include "parcer_in_parallel.h"

#include <stdio.h>
#include <time.h>

#define NANOSECONDS 1000000000.0

int main(int argc, char** argv) {
    fprintf(stdout, "%s\n", "Hello, World");

    // test_foo();

    // char* test = readfile(stdin);
    // fprintf(stdout, "%s\n", test);
    // free(test);

    FILE* f = fopen("../test1.dat", "r");
    // char* test = readfile(f);
    // fprintf(stdout, "%s\n", test);

    long int tone = 0;

//---------------------

    struct timespec start, finish, start_parallel, finish_parallel;

    clock_gettime(CLOCK_MONOTONIC, &start);
    main_workflow(f, &tone);
    fprintf(stderr, "%ld\n", tone);


    clock_gettime(CLOCK_MONOTONIC, &finish);

    double time = (finish.tv_sec - start.tv_sec);

    time += (finish.tv_nsec - start.tv_nsec) / NANOSECONDS;

    printf("Время выполнения последовательного алгоритма:%lf\n", time);

   clock_gettime(CLOCK_MONOTONIC, &start_parallel);

    pthread_main_workflow(f, &tone);

    clock_gettime(CLOCK_MONOTONIC, &finish_parallel);

    double time_parallel = (finish_parallel.tv_sec - start_parallel.tv_sec);

    time_parallel += (finish_parallel.tv_nsec - start_parallel.tv_nsec) / NANOSECONDS;

    printf("Время выполнения параллельного алгоритма:%lf\n", time_parallel);



//--------------------    

    fclose(f);

    // fprintf(stdout, "%ld\n", tone);
    fprintf(stdout, "%s\n", "finish");

    // pthread_exit(0);

    return 0;
}
