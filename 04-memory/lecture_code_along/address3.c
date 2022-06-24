#include <stdio.h>

int main(void)
{
    char *s = "HI!";

    printf("%c\n", s[0]);
    printf("%c\n", s[1]);
    printf("%c\n", s[2]);

    // same as above, this time using pointer arithmetic
    printf("%c\n", *s);
    printf("%c\n", *(s + 1));
    printf("%c\n", *(s + 2));

// -----------------------------------------------------

    int numbers[] = {4, 6, 8, 2, 7, 5, 0};

    printf("%i\n", numbers[0]);
    printf("%i\n", numbers[1]);
    printf("%i\n", numbers[2]);
    printf("%i\n", numbers[3]);
    printf("%i\n", numbers[4]);
    printf("%i\n", numbers[5]);

    // same as above, this time using pointer arithmetic
    printf("%i\n", *numbers);
    printf("%i\n", *(numbers + 1));
    printf("%i\n", *(numbers + 2));
    printf("%i\n", *(numbers + 3));
    printf("%i\n", *(numbers + 4));
    printf("%i\n", *(numbers + 5));
}
