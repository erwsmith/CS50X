#include <stdio.h>
#include <cs50.h>

int collatz(int n);

int main(void)
{
    int number = get_int("Starting number: ");
    printf("%d\n", collatz(number));
    return 0;
}

int collatz(int n)
{
    if (n == 1)
    // base case
    {
        return 0;
    }
    else if (n % 2 == 0)
    // even recursive case
    {
        return 1 + collatz(n / 2);
    }
    else
    // recursive case odd
    {
        return 1 + collatz((3 * n) + 1);
    }
}