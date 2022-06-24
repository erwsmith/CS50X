#include <stdio.h>
#include <cs50.h>

int fibonacci(int n);

int main(void)
{
    int number = get_int("How many fibonacci digits? ");

    for (int i = 0; i < number; i++)
    {
        printf("%d\n", fibonacci(i));
    }
    return 0;
}

int fibonacci(int n)
{
    if (n == 1 || n == 0)
        // base cases
        return n;
    else
        // recursive case
        return fibonacci(n - 1) + fibonacci(n - 2);
}