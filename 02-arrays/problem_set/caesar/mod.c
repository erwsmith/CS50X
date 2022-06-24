#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
    int x = get_int("int: " );
    int y = round(x % 26);
    printf("%i\n", y);
}