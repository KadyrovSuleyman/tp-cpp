#include "matrix.h"

int main() {
    Matrix* target;
    target = create_matrix(stdin);

    // FILE* target_file = fopen("test", "r");
    // target = create_matrix(target_file);

    // if (!target_file) {
    //     fclose(target_file);
    //     return -1;
    // }

    // FILE* result_file = fopen("result", "w+");

    print_matrix(target, stdout);

    size_t minor_row = read_data(stdin);
    size_t minor_col = read_data(stdin);

    Matrix* result;
    result = minor_matrix(target, target->rows, target->cols, minor_row, minor_col);

    if (print_matrix(result, stdout)) {
        fprintf(stderr, "%s\n", "Error");
    }
    if (is_matrix_equal(target, result)) {
        fprintf(stderr, "%s\n", "Error");
    }

    free_matrix(result);
    free_matrix(target);

    return 0;
}
