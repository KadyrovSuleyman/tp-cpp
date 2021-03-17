#include "gtest/gtest.h"


extern "C" {
    #include "matrix.h"
    #include <iostream>
    #include <errno.h>
    #include <stdlib.h>
    #include <stdio.h>
    #include <ctype.h>
    #include <string.h>
}

TEST(first_test, malloc_matrix) {
    Matrix* t = malloc_matrix(1, 1);
    t->item[0][0] = 5;
    ASSERT_EQ(t->item[0][0], 5);
    free_matrix(t);
}

TEST(is_matrix_equal, case_1) {

    FILE* l = fopen("./project/tests/data/case_1/left", "r");
    FILE* r = fopen("./project/tests/data/case_1/right", "r");

    Matrix* left = create_matrix(l);
    Matrix* right = create_matrix(r);

    ASSERT_TRUE(is_matrix_equal(left, right));

    free_matrix(left);
    free_matrix(right);

    fclose(l);
    fclose(r);
}

TEST(minor_matrix, case_2) {

    FILE* input_file = fopen("./project/tests/data/case_2/input", "r");
    FILE* output_file = fopen("./project/tests/data/case_2/output", "r");

    Matrix* input = create_matrix(input_file);
    Matrix* output = create_matrix(output_file);

    Matrix* result = minor_matrix(input, input->rows, input->cols, 1, 1);

    ASSERT_TRUE(is_matrix_equal(result, output));

    free_matrix(input);
    free_matrix(output);
    free_matrix(result);

    fclose(input_file);
    fclose(output_file);
}


int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}