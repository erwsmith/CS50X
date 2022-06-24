// WRITTEN BY ERIC 8 APRIL 2022

#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>

char substitute(char c, string key);

int main(void)
{
    char enciphered_char = substitute('z', "YTNSHKVEFXRBAUQZCLWDMIPGJO");
    printf("cipher char: %c\n", (char) enciphered_char);
}

char substitute(char c, string key)
{
    // get ascii dec value of c
    int letter_ascii = (int) c;
    int val = 0;
    char enciphered_char = '#';
    if (letter_ascii < 65 || letter_ascii > 122 || (letter_ascii > 90 && letter_ascii < 97))
    {
        // if c is not a letter, return c unchanged
        return c;
    }
    else if (islower(c))
    {
        // if c is a lowercase letter
        // set 'a-z' values to 0-26
        val = letter_ascii - 97;
        // apply substitution
        enciphered_char = key[val];
    }
    else
    {
        // if c is an uppercase letter
        // set 'A-Z' values to 0-26
        val = letter_ascii - 65;
        // printf("val: %i\n", val);
        // apply substitution
        enciphered_char = key[val];
        // printf("key at index val: %i\n", key[val]);
    }
    return (char) enciphered_char;
}