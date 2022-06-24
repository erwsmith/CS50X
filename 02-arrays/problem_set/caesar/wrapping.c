#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>

char rotate(char c, int rotate_by);

int main(void)
{
    printf("%c\n", rotate('A', 1));
}

char rotate(char c, int rotate_by)
{
    int letter_ascii = (int) c;
    int val = 0;
    char enciphered = '#';
    rotate_by = round(rotate_by % 26);
    if (letter_ascii < 65 || letter_ascii > 122 || (letter_ascii > 90 && letter_ascii < 97))
    {
        return c;
    }
    else
    {
        if (islower(c))
        {
            val = letter_ascii - 97;
            enciphered = ((val + rotate_by) % 26) + 97;
        }
        else
        {
            val = letter_ascii - 65;
            enciphered = ((val + rotate_by) % 26) + 65;
        }
        return enciphered;
    }
}