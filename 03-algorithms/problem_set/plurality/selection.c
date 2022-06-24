#include <cs50.h>
#include <stdio.h>
#include <string.h>


// int numbers[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
// int numbers[] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
int numbers[] = {5, 9, 0, 7, 4, 1, 6, 3, 8, 2};
int n = 10;
int sorted_numbers[10];
int min = 999;

int main(void)
{
    for (int i = 0; i < n - 1; i++)
    {
        if (numbers[i] > numbers[i +1])
        {
            swap(numbers[i] > numbers[i +1])
        }
        // printf("%i, %i\n", numbers[i], numbers[i + 1]);
    }

    // print_array(sorted_numbers);

}

// void print_array()
//     for (int i = 0; i < n; i++)
//     {
//         printf("%i\n", sorted_numbers[i]);
//     }