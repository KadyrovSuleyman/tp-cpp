#include "gtest/gtest.h"

#define NANOSECONDS 1000000000.0

extern "C" {
    #include "parcer_in_series.h"
    #include "parcer_in_parallel.h"

    #include <stdio.h>
    #include <time.h>
}

TEST(in_series_mmap_test, main_workflow) {
    FILE* f = fopen("./project/test/data/case_1/test.dat", "r");
    long int tone = 0;
    main_workflow(f, &tone);
    fclose(f);

    ASSERT_EQ(tone, -3);
}

TEST(in_series_malloc_test, main_workflow) {
    long int tone = 0;
    main_workflow(stdin, &tone);

    ASSERT_EQ(tone, -3); 
}

TEST(in_parallel_mmap_test, pthread_main_workflow) {
    FILE* f = fopen("./project/test/data/case_1/test.dat", "r");
    long int tone = 0;
    pthread_main_workflow(f, &tone);
    fclose(f);

    ASSERT_EQ(tone, -3); 
}

TEST(compare_methods, main_workflow) {
    FILE* f = fopen("./project/test/data/case_2/test.dat", "r");
    long int tone_in_series = 0;

    struct timespec start_in_series, finish_in_series, start_in_parallel, finish_in_parallel;

    clock_gettime(CLOCK_MONOTONIC, &start_in_series);
    main_workflow(f, &tone_in_series);
    clock_gettime(CLOCK_MONOTONIC, &finish_in_series);
    fprintf(stdout, "%ld\n", tone_in_series);

    double time = (finish_in_series.tv_sec - start_in_series.tv_sec);
    time += (finish_in_series.tv_nsec - start_in_series.tv_nsec) / NANOSECONDS;
    fprintf(stdout, "Parcer in series: %lf\n", time);

    long int tone_in_parallel = 0;
    clock_gettime(CLOCK_MONOTONIC, &start_in_parallel);
    pthread_main_workflow(f, &tone_in_parallel);
    clock_gettime(tone_in_parallel, &finish_in_parallel);
    fprintf(stdout, "%ld\n", tone_in_parallel);

    time = (finish_in_parallel.tv_sec - start_in_parallel.tv_sec);
    time += (finish_in_parallel.tv_nsec - start_in_parallel.tv_nsec) / NANOSECONDS;
    fprintf(stdout, "Parcer in parallel: %lf\n", time);

    fclose(f);

    ASSERT_EQ(tone_in_series, tone_in_parallel);
}


int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}