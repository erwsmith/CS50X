// WRITTEN BY ERIC 8 APRIL 2022

#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>

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

bool only_letters(string key);

int main(void)
{
    if (only_letters("VCHPRZGJNTLSKFADQWAXEUYMOJ"))
    {
        printf("True\n");
    }
    else
    {
        printf("False\n");
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
        // if char at i is alphabetical, add to alpha count
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
    // printf("for key: %s\nalpha_count = %i\nnon_alpha_count = %li\n", key, alpha_count, non_alpha_count);
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