#include <stdio.h>
#include <cs50.h>

int factorial(int n);

int main(void)
{
    int number = get_int("Enter a positive integer: ");
    int result = factorial(number);
    printf("%i factorial = %d\n", number, result);
    return 0;
}

int factorial(int n)
{
    if (n > 1)
        // recursive case
        return n * factorial(n - 1);
    else
        // base case
        return n;
}