#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

bool only_digits(void);

int main(void)
{
    if (only_digits())
    {
        printf("True\n");
    }
    else
    {
        printf("False\n");
    }
}


bool only_digits(void)
{
    string key = "25";
    // string key = "hello";

    int length = strlen(key);
    int digit_count = 0;
    int non_digit_count = 0;

    for (int i = 0; i < length; i++)
    {
        if (isdigit(key[i]))
        {
            digit_count++;
        }
        else
        {
            non_digit_count++;
        }
    }
    if (non_digit_count > 0)
    {
        return false;
    }
    else
    {
        return true;
    }
}