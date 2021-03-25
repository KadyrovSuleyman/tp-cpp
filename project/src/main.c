#include "parcer.h"

#include <stdio.h>

int main(int argc, char** argv) {
    fprintf(stdout, "%s\n", "Hello, World");

    // char* test = readfile(stdin);
    // fprintf(stdout, "%s\n", test);
    // free(test);

    FILE* f = fopen("../test.dat", "r");
    // char* test = readfile(f);
    // fprintf(stdout, "%s\n", test);

    main_workflow_mmap(f);
    
    fclose(f);

    // fprintf(stdout, "%zu\n", munmap(test, ));

    fprintf(stdout, "%s\n", "finish");



    return 0;

    
}
