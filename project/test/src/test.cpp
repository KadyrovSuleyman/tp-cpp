#include "gtest/gtest.h"

extern "C" {
    #include "parcer_in_series.h"
    #include "parcer_in_parallel.h"
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

TEST(in_parallel_mmap_test, main_workflow) {
    FILE* f = fopen("./project/test/data/case_1/test.dat", "r");
    long int tone = 0;
    pthread_main_workflow(f, &tone);
    fprintf(stdout, "%ld\n", tone);
    fclose(f);

    ASSERT_EQ(tone, -3); 
}


int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}