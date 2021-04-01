#include "parcer_in_series.h"
#include "parcer_in_parallel.h"

#include <stdio.h>
#include <time.h>

#define NANOSECONDS 1000000000.0

int main(int argc, char** argv) {
    FILE* f = fopen("../test.dat", "r");
    long int tone = 0;

    struct timespec start_in_series, finish_in_series, start_in_parallel, finish_in_parallel;

    clock_gettime(CLOCK_MONOTONIC, &start_in_series);
    main_workflow(f, &tone);
    clock_gettime(CLOCK_MONOTONIC, &finish_in_series);
    fprintf(stdout, "%ld\n", tone);

    double time = (finish_in_series.tv_sec - start_in_series.tv_sec);
    time += (finish_in_series.tv_nsec - start_in_series.tv_nsec) / NANOSECONDS;
    fprintf(stdout, "Parcer in series: %lf\n", time);


    tone = 0;
    clock_gettime(CLOCK_MONOTONIC, &start_in_parallel);
    pthread_main_workflow(f, &tone);
    clock_gettime(CLOCK_MONOTONIC, &finish_in_parallel);
    fprintf(stdout, "%ld\n", tone);

    time = (finish_in_parallel.tv_sec - start_in_parallel.tv_sec);
    time += (finish_in_parallel.tv_nsec - start_in_parallel.tv_nsec) / NANOSECONDS;
    fprintf(stdout, "Parcer in parallel: %lf\n", time);
 
    fclose(f);
    return 0;
}
