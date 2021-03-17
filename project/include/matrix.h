#ifndef PROJECT_INCLUDE_MATRIX_H_
#define PROJECT_INCLUDE_MATRIX_H_


#include <stdio.h>

#define MAX_DATA_LENGTH 10

typedef struct {
    size_t rows;
    size_t cols;
    double** item;
} Matrix;

int error_handler(const char* invalid_func);
int print_matrix(const Matrix* target, FILE* os);

Matrix* malloc_matrix(size_t rows, size_t cols);
int free_matrix(Matrix* target);

Matrix* create_matrix(FILE* is);
double read_data(FILE* is);
int is_matrix_equal(const Matrix* left, const Matrix* right);
Matrix* minor_matrix(const Matrix* target, size_t rows, size_t cols,
    size_t minor_row, size_t minor_col);

#endif  // PROJECT_INCLUDE_MATRIX_H_
