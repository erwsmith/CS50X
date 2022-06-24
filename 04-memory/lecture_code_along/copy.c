#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>


int main(void)
{
    char *s = get_string("s: ");

    // to create an actual copy of s in variable t
    char *t = malloc(strlen(s) + 1);

    // make sure there's enough memory available
    // malloc can fail if there's not enough memory
    // NULL is zero in the context of pointers
    if (t == NULL)
    {
        return 1;
    }

    // int n = strlen(s) + 1;
    // for (int i = 0; i < n; i++)
    // {
    //     t[i] = s[i];
    // }

    // strcpy() does the same as for loop above
    strcpy(t, s);

    // make sure length of t is greater than 0
    if (strlen(t) > 0)
    {
        t[0] = toupper(t[0]);
    }

    printf("s: %s\n", s);
    printf("t: %s\n", t);

    // free the memory that was allocated to t now that we're done with it
    free(t);
}