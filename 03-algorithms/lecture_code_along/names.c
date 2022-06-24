// Implements linear search for names

#include <cs50.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    string names[] = {"Bill", "Charlie", "Fred", "George", "Ginny", "Percy", "Ron"};

    // Search for a name using strcmp(), if it returns 0, it means the strings are equal
    for (int i = 0; i < 7; i++)
    {
        if (strcmp(names[i], "Hermione") == 0)
        {
            printf("Found\n");
            return 0;
        }
    }
    printf("Not found\n");
    return 1;
}
