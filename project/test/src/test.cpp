#include "gtest/gtest.h"

extern "C" {
    #include "parcer_in_series.h"
    #include "parcer_in_parallel.h"
}

TEST(in_serial_mmap_test, main_workflow) {
    FILE* f = fopen(".../test1.dat", "r");
    long int tone = 0;
    main_workflow(f, &tone);
    fprintf(stdout, "%ld\n", tone);
    fclose(f);
}

// TEST(in_serial_malloc_test, main_workflow) {
//     long int tone = 0;
//     main_workflow(stdin, &tone);
//     fprintf(stdout, "%ld\n", tone);
// }

// TEST(in_parallel_mmap_test, main_workflow) {
//     FILE* f = fopen("../test1.dat", "r");
//     long int tone = 0;
//     pthread_main_workflow(f, &tone);
//     fprintf(stdout, "%ld\n", tone);
//     fclose(f);    
// }

// TEST(in_parallel_malloc_test, main_workflow) {
//     long int tone = 0;
//     pthread_main_workflow(stdin, &tone);
//     fprintf(stdout, "%ld\n", tone);
// }


int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}