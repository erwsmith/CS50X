#include <cs50.h>
#include <stdio.h>
#include <string.h>

void tabulate(string e);


int ranks[] = {0, 1, 2};
string names[] = {"a", "b", "c"};

int main(void)
{
    string eliminate = get_string("name to eliminate: ");
    tabulate(eliminate);
}

void tabulate(string e)
{
    for (int i = 0; i < 3; i++)
    {
        if (strcmp(names[i], e) == 0)
        {
            printf("%s has been eliminated\n", names[i]);
        }
    }
}

