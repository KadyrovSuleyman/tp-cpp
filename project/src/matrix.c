// Составить программу нахождения минорных матриц. Под минорной матрицей для
// ячейки с индексами (i, j) понимается матрица, получаемая удалением из
// исходной матрицы элементов на строке i и столбце j, Исходная прямоугольная
// матрица задана в виде вектора векторов. Поиск оформить в виде функции,
// получающей на вход двумерную матрицу, ее размеры по каждому измерению,
// а также индексы ячейки, для которой требуется построить минорную матрицу.
// На выход функция должна возвращать указатель на результирующую структуру

#include "matrix.h"
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define unlikely(x)     __builtin_expect((x), 0)

//----------------------
int error_handler(const char* invalid_func) {
    if (unlikely(errno)) {
        perror(invalid_func);
        return -1;
    }

    return 0;
}

int print_matrix(const Matrix* target, FILE* os) {
    if (unlikely(!target || !os)) {
        fprintf(stderr, "%s\n", "Matrix or stream aren't exist");
        return -1;
    }

    fprintf(os, "%zu %zu\n", target->rows, target->cols);
    for (size_t i = 0; i < target->rows; ++i) {
        for (size_t j = 0; j < target->cols; ++j) {
            fprintf(os, "%lf ", target->item[i][j]);
        }
        fprintf(os, "\n");
    }
    return 0;
}

Matrix* malloc_matrix(const size_t rows, const size_t cols) {
    Matrix* result = (Matrix*)malloc(sizeof(Matrix));
    if (errno == ENOTTY) {
        errno = 0;
    }
    if (unlikely(error_handler("malloc"))) {
        free_matrix(result);
        return NULL;
    }
    result->rows = rows;
    result->cols = cols;

    result->item = (double**)malloc(rows * sizeof(double*));
    if (errno == ENOTTY) {
        errno = 0;
    }
    if (unlikely(error_handler("malloc"))) {
        free(result->item);
        free_matrix(result);
        return NULL;
    }

    for (size_t i = 0; i < rows; ++i) {
        result->item[i] = (double*)malloc(cols * sizeof(double));
        if (errno == ENOTTY) {
            errno = 0;
        }
        if (unlikely(error_handler("malloc"))) {
            for (size_t j = 0; j < i; ++j) {
                free(result->item[j]);
            }
            free(result->item);
            free_matrix(result);
            return NULL;
        }
    }

    return result;
}

int free_matrix(Matrix* target) {
    if (unlikely(!target)) {
        return -1;
    }

    for (size_t i = 0; i < target->rows; ++i) {
        free(target->item[i]);
    }
    free(target->item);
    free(target);

    return 0;
}

Matrix* create_matrix(FILE* is) {
    if (unlikely(!is)) {
        fprintf(stderr, "%s\n", "Input stream isn't exist");
        return NULL;
    }

    double input_data = read_data(is);
    if (unlikely(error_handler("fscanf"))) {
        return NULL;
    }

    size_t rows = (size_t)input_data;
    if (unlikely(rows != input_data)) {
        fprintf(stderr, "%s\n", "Invalid input data");
        return NULL;
    }

    input_data = read_data(is);
    size_t cols = (size_t)input_data;
    if (unlikely(cols != input_data)) {
        fprintf(stderr, "%s\n", "Invalid input data");
        return NULL;
    }

    Matrix* result = malloc_matrix(rows, cols);
    if (unlikely(!result)) {
        return NULL;
    }

    result->rows = rows;
    result->cols = cols;
    for (size_t i = 0; i < result->rows; ++i) {
        for (size_t j = 0; j < result->cols; ++j) {
            result->item[i][j] = read_data(is);
            if (unlikely(error_handler("fscanf"))) {
                free_matrix(result);
                return NULL;
            }
        }
    }

    // if (read_data(is) != EOF) {
    //     fprintf(stderr, "%s\n", "Invalid input data");
    //     free_matrix(result);
    //     return NULL;
    // }
    // errno = !errno

    return result;
}

double read_data(FILE* is) {
    char temp[MAX_DATA_LENGTH];
    if (unlikely(fscanf(is, "%9s", temp) < 0)) {
        errno = EIO;
        return -1;
    }

    size_t i = 0;
    if (temp[i] == '-') {
        ++i;
    }
    while (unlikely(temp[i] != '\0')) {
        if (!isdigit(temp[i]) && temp[i] != '.') {
            errno = EBADMSG;
            return -1;
        }
        ++i;
    }

    double result = strtod(temp, NULL);
    if (unlikely(error_handler("strtod"))) {
        return -1;
    }

    return result;
}

int is_matrix_equal(const Matrix* left, const Matrix* right) {
    if (unlikely(!left || !right)) {
        errno = EIO;
        return -1;
    }

    if (unlikely((left->rows != right->rows) || (left->cols != right->cols))) {
        return 0;
    }

    for (size_t i = 0; i < left->rows; ++i) {
        for (size_t j = 0; j < left->cols; ++j) {
            if (unlikely(left->item[i][j] != right->item[i][j])) {
                return 0;
            }
        }
    }

    return 1;
}

Matrix* minor_matrix(const Matrix* target, const size_t rows, const size_t cols,
const size_t minor_row, const size_t minor_col) {
    if (unlikely(!target || !rows || !cols)) {
        errno = EIO;
        return NULL;
    }

    Matrix* result = malloc_matrix(rows - 1, cols - 1);
    if (unlikely(!result)) {
        return NULL;
    }

    result->rows = target->rows - 1;
    result->cols = target->cols - 1;

    for (size_t it = 0, ir = 0; ir < result->rows; ++it, ++ir) {
        if (unlikely(it == minor_row)) {
            ++it;
        }
        for (size_t jt = 0, jr = 0; jr < result->cols; ++jt, ++jr) {
            if (unlikely(jt == minor_col)) {
                ++jt;
            }
            result->item[ir][jr] = target->item[it][jt];
        }
    }

    return result;
}
