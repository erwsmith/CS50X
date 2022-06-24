#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    // malloc returns the address of a chunk of memory
    int *x = malloc(3 * sizeof(int));
    x[0] = 72;
    x[1] = 73;
    x[2] = 33;
    free(x);
    // use 'valgrind ./memory' in command line to check for memory issues
}