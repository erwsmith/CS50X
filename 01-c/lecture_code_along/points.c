#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // comment example
    const int MINE = 2;
    int points = get_int("How many points did you lose? ");
    if (points < MINE)
    {
        printf("you lost fewer points than me.\n");
    }
    else if (points > MINE)
    {
        printf("you lost more points than me\n");
    }
    else
    {
        printf("you lost the same number of points as me\n");
    }
}
