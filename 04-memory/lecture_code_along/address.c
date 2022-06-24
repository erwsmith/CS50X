#include <stdio.h>

int main(void)
{
    int n = 50;
    int c = n;

    // &n is the address of n
    // if you want to store an address, you have to use * like this:
    // p is a 'pointer'
    int *p = &n;
    int *p2 = &c;

    // use %p in printf() since we're printing a pointer
    // print pointer variable p
    // printf("%p\n", p);

    // alternatively, without using *p pointer
    printf("%p\n", &n);
    printf("%p\n", &c);

    // print the integer at a certain address 'dereference operator'
    printf("%i\n", *p);
    printf("%i\n", *p2);
}