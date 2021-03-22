#include "parcer.h"

#include <stdio.h>

int main(int argc, char** argv) {
    fprintf(stdout, "%s\n", "Hello, World");

    char* test = readfile(stdin);


    fprintf(stdout, "%s\n", "finish");
    return 0;

    
}
