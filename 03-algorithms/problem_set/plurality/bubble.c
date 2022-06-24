#include <cs50.h>
#include <stdio.h>
#include <string.h>


// int numbers[] = {5, 9, 0, 7, 4, 1, 6, 3, 8, 2};
int numbers[] = {3, 6, 0, 8, 4, 1, 9, 5, 7, 2};
int n = 10;

int main(void)
{
    // print initial array
    for (int i = 0; i < n; i++)
    {
        printf("%i ", numbers[i]);
    }
    printf("\n");

    // run bubble sort
    // repeat n - 1 times
    for (int i = 0; i < n - 1; i++)
    {
        // for j from 0 to n - 2
        for (int j = 0; j <= n - 2; j++)
        {
            // if numbers are out of order (sorting ascending)
            if (numbers[j] > numbers[j + 1])
            {
                // swap numbers
                int temp = numbers[j];
                numbers[j] = numbers[j + 1];
                numbers[j + 1] = temp;
            }
        }
    }

    // print sorted array
    for (int i = 0; i < n; i++)
    {
        printf("%i ", numbers[i]);
    }
    printf("\n");
}