/*
WRITTEN BY ERIC 8 APRIL 2022

Description from CS50X:
In a substitution cipher, we “encrypt” a message by replacing every letter with another letter.
To do so, we use a key: in this case, a mapping of each of the letters of the alphabet to the letter
it should correspond to when we encrypt it. To “decrypt” the message, the receiver of the message
would need to know the key, so that they can reverse the process: translating the encrypt text
(generally called ciphertext) back into the original message (generally called plaintext).

A key, for example, might be the string NQXPOMAFTRHLZGECYJIUWSKDVB. This 26-character key means
that A (the first letter of the alphabet) should be converted into N (the first character of the
key), B (the second letter of the alphabet) should be converted into Q (the second character of
the key), and so forth.

A message like HELLO, then, would be encrypted as FOLLE, replacing each of the letters according
to the mapping determined by the key.

Let’s write a program called substitution that enables you to encrypt messages using a
substitution cipher. At the time the user executes the program, they should decide, by providing
a command-line argument, on what the key should be in the secret message they’ll provide at runtime.
*/

#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>

char substitute(char c, string key);
bool only_letters(string key);

int main(int argc, string argv[])
{
    // check if correct number of args have been entered
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    else if (strlen(argv[1]) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }
    else if (only_letters(argv[1]))
    {
        // convert argv[1] to an int
        string key = argv[1];
        string plain = get_string("plaintext: ");
        string cipher = plain;
        int length = strlen(plain);
        // iterate through plain text, encipher on each char, return enciphered string
        for (int i = 0; i < length; i++)
        {
            cipher[i] = substitute(plain[i], key);
        }
        printf("ciphertext:%s\n", cipher);
        return 0;
    }
    else
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
}

bool only_letters(string key)
{
    // checks if string is comprised of only digits
    int length = strlen(key);
    int alpha_count = 0;
    long non_alpha_count = 0;
    for (int i = 0; i < length; i++)
    {
        // if char at i is alphabetical, check for duplicates, then add to alpha count
        if (isalpha(key[i]))
        {
            if (i > 0)
            {
                for (int j = 0; j < i; j++)
                {
                    if (key[i] == key[j])
                    {
                        return false;
                    }
                }
            }
            alpha_count++;
        }
        else
        {
            // if char at i is not a alphabetical, add to non alpha count
            non_alpha_count++;
            return false;
        }
    }
    // if there are any non-alphabetical chars in the key, or if there are any duplicate alpha values, return false
    if (non_alpha_count > 0)
    {
        return false;
    }
    else
    {
        return true;
    }
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
        enciphered_char = tolower(key[val]);
    }
    else
    {
        // if c is an uppercase letter
        // set 'A-Z' values to 0-26
        val = letter_ascii - 65;
        // printf("val: %i\n", val);
        // apply substitution
        enciphered_char = toupper(key[val]);
        // printf("key at index val: %i\n", key[val]);
    }
    return (char) enciphered_char;
}

/*
test keys
good:
VCHPRZGJNTLSKFBDQWAXEUYMOI
YTNSHKVEFXRBAUQZCLWDMIPGJO
NQXPOMAFTRHLZGECYJIUWSKDVB

not all digits:
YTNSHKVEFXRBAUQZCLWDMIPG12

basic duplicate chars:
AAAPRZGJNTLSKFBDQWAXEUYMOI

special duplicate chars:
VCHPRZGJNTLSKFADQWAXEUYMOJ
*/