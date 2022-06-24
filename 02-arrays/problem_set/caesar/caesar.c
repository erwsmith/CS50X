// WRITTEN BY ERIC 8 APRIL 2022

#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>

bool only_digits(string key);
char rotate(char c, int n);

int main(int argc, string argv[])
{
    // check if correct number of args have been entered
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    // check if string is only digits
    if (only_digits(argv[1]))
    {
        // convert argv[1] to an int
        int key = atoi(argv[1]);
        string plain = get_string("plaintext: ");
        // iterate through plain text, rotate on each char, return enciphered string
        string cipher = plain;
        int length = strlen(plain);
        for (int i = 0; i < length; i++)
        {
            cipher[i] = rotate(cipher[i], key);
        }
        printf("ciphertext: %s\n", cipher);
    }
    else
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
}

bool only_digits(string key)
{
    // checks if string is comprised of only digits
    int length = strlen(key);
    int digit_count = 0;
    int non_digit_count = 0;

    for (int i = 0; i < length; i++)
    {
        // if char at i is a digit, add to digit count
        if (isdigit(key[i]))
        {
            digit_count++;
        }
        else
        {
            // if char at i is not a digit, add to non digit count
            non_digit_count++;
        }
    }
    // if there are any non digits in the key, return false
    if (non_digit_count > 0)
    {
        return false;
    }
    else
    {
        return true;
    }
}

char rotate(char c, int rotate_by)
{
    // 'rotate' letter by the given 'rotate_by' number, wrapping after z
    // example 1, rotate('a', 2) returns 'c'
    // example 2, rotate('z', 1) returns 'a'
    // get ascii dec value of c
    int letter_ascii = (int) c;
    int val = 0;
    char enciphered = '#';
    // check if c is a letter, if it's not a letter, return just c unchanged
    if (letter_ascii < 65 || letter_ascii > 122 || (letter_ascii > 90 && letter_ascii < 97))
    {
        return c;
    }
    else
    {
        // if c is a letter, upper or lowercase
        // for lowercase letters:
        if (islower(c))
        {
            // set 'a' value to 0
            val = letter_ascii - 97;
            // apply the rotation with wrapping
            enciphered = ((val + rotate_by) % 26) + 97;
        }
        else
        {
            // for uppercase letters:
            // set 'A' value to 0
            val = letter_ascii - 65;
            enciphered = ((val + rotate_by) % 26) + 65;
        }
        return enciphered;
    }
}