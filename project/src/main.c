#include "parcer.h"

#include <stdio.h>

int main(int argc, char** argv) {
    fprintf(stdout, "%s\n", "Hello, World");

    char* test = readfile(stdin);

    fprintf(stdout, "%s\n", test);


    fprintf(stdout, "%s\n", "finish");

    free(test);

    return 0;

    
}
