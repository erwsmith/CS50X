#include <cs50.h>
#include <stdio.h>

int main(void)
{
// get user input for pyramid height
    int n;
    do
    {
        n = get_int("Height of pyramid (range = 1-8 inclusive): ");
    }
    while (n < 1 || n > 8);

// print pyramid
    // for each row
    for (int i = 0; i < n; i++)
    {
        // print a decrementing number of spaces
        for (int spaces = n - 2; spaces >= i; spaces--)
        {
            printf(" ");
        }
        // print an incrementing number of #s
        for (int j = 0; j <= i; j++)
        {
            printf("#");
        }
        // print a newline at the end of the 'row' for loop
        printf("\n");
    }
}