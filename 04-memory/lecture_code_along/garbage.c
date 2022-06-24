#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int scores[3];
    for (int i = 0; i < 3; i++)
    {
        printf("%i\n", scores[i]);
    }

    /* values were not initialized
     output is 'garbage'

    1308172560
    32765
    0

    */
}