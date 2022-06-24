/*
WRITTEN BY ERIC 7 APRIL 2022

Description from CS50X:
Most credit cards use an algorithm invented by Hans Peter Luhn of IBM.
According to Luhn’s algorithm, you can determine if a credit card
number is (syntactically) valid as follows:

Multiply every other digit by 2, starting with the number’s
second-to-last digit, and then add those products’ digits together.
Add the sum to the sum of the digits that weren’t multiplied by 2.
If the total’s last digit is 0 (or, put more formally, if the
total modulo 10 is congruent to 0), the number is valid!
*/

#include <cs50.h>
#include <stdio.h>
#include <math.h>

int lenHelper(long x)
{
    if (x >= 1000000000000000)
    {
        return 16;
    }
    else if (x >= 100000000000000)
    {
        return 15;
    }
    else if (x >= 10000000000000)
    {
        return 14;
    }
    else if (x >= 1000000000000)
    {
        return 13;
    }
    else if (x >= 10)
    {
        return 2;
    }
    else
    {
        return 0;
    }
}


int main(void)
{
    // Prompt for input to get credit card number from user
    long num;
    do
    {
        num = get_long("Number: ");
    }
    while (num < 0);

    // Check for card length
    const long num_final = num;
    int num_len = lenHelper(num);
    long denom = 10;
    int set1 = 0;
    int set2 = 0;
    int second_digit = 0;
    int first_digit = 0;

    // Implement Luhn's Algorithm to validate credit card number
    // for each digit in card number
    for (long i = 0; i < num_len; i++)
    {
        long mod = round(num % denom);
        long digit = round(mod / (denom / 10));

        // get first 2 digits in card number
        if (i == num_len - 2)
        {
            second_digit = digit;
            //printf("second digit is %i\n", second_digit);
        }
        else if (i == num_len - 1)
        {
            first_digit = digit;
            //printf("first digit is: %i\n", first_digit);
        }
        //printf("%li\n", digit);

        // subtract the mod value from num, multiply denominator by 10
        num -= mod;
        denom *= 10;
        // set1: starting with 2nd to last digit, multiply each value by 2,
        // then add those products’ digits together
        if (i % 2 != 0)
        {
            int dx2 = digit * 2;
            //printf("%i\n", dx2);
            //if the product of the digit and 2 is greater than 10, split the digits and sum them
            if (lenHelper(dx2) == 2)
            {
                int dx2_mod = dx2 % 10;
                //printf("%i\n", 1 + dx2_mod);
                int dx2_digit_sum = 1 + dx2_mod;
                set1 += dx2_digit_sum;
            }
            else
            {
                set1 += (digit * 2);
            }
        }
        // Add the sum to the sum of the digits that weren’t multiplied by 2
        else
        {
            if (lenHelper(digit) == 2)
            {
                int digit_mod = digit % 10;
                int digit_sum = 1 + digit_mod;
                set2 += digit_sum;
            }
            else
            {
                set2 += digit;
            }
        }
    }
    // Check if the total’s last digit is 0 (if the total modulo 10 is congruent to 0), if True, the number is valid!
    if ((set1 + set2) % 10 != 0)
    {
        printf("INVALID\n");
    }
    // Print results
    // Check starting digits
    // if number starts with: 34 or 37 and is 15-digits long, "AMEX"
    else if (num_len == 15)
    {
        if (first_digit != 3)
        {
            printf("INVALID\n");
        }
        else if (second_digit == 4 || second_digit == 7)
        {
            printf("AMEX\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    // if starts with: 51, 52, 53, 54, or 55 and is 16-digits long, "MASTERCARD"
    else if (num_len == 16)
    {
        if (first_digit == 5 && second_digit >= 1 && second_digit <= 5)
        {
            printf("MASTERCARD\n");
        }
        else if (first_digit == 4)
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    // if starts with: 4, and 13 digits long, "VISA"
    else if (num_len == 13)
    {
        if (first_digit == 4)
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }
}