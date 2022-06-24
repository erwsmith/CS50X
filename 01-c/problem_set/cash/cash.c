#include <cs50.h>
#include <stdio.h>
#include <math.h>

int get_cents(void);
int calculate_quarters(int cents);
int calculate_dimes(int cents);
int calculate_nickels(int cents);
int calculate_pennies(int cents);

int main(void)
{
    // Ask how many cents the customer is owed
    int cents = get_cents();

    // Calculate the number of quarters to give the customer
    int quarters = calculate_quarters(cents);
    cents = cents - quarters * 25;

    // Calculate the number of dimes to give the customer
    int dimes = calculate_dimes(cents);
    cents = cents - dimes * 10;

    // Calculate the number of nickels to give the customer
    int nickels = calculate_nickels(cents);
    cents = cents - nickels * 5;

    // Calculate the number of pennies to give the customer
    int pennies = calculate_pennies(cents);
    cents = cents - pennies * 1;

    // Sum coins
    int coins = quarters + dimes + nickels + pennies;

    // Print total number of coins to give the customer
    printf("%i\n", coins);
}

int get_cents(void)
{
    // prompts the user for a number of cents and then returns that number as an int.
    // If the user inputs a negative int, prompt the user again
    int c;
    do
    {
        c = get_int("Change owed: ");
    }
    while (c < 0);
    return c;
}

int calculate_quarters(int cents)
{
    // calculates (and returns as an int) how many quarters a customer should be given
    int q = 0;
    q = floor(cents / 25);
    return q;
}

int calculate_dimes(int cents)
{
    // calculates (and returns as an int) how many dimes a customer should be given
    int d = 0;
    d = floor(cents / 10);
    return d;
}

int calculate_nickels(int cents)
{
    // calculates (and returns as an int) how many nickels a customer should be given
    int n = 0;
    n = floor(cents / 5);
    return n;
}

int calculate_pennies(int cents)
{
    // calculates (and returns as an int) how many pennies a customer should be given
    int p = 0;
    p = cents;
    return p;
}
