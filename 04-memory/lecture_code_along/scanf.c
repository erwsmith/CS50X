#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    char *s = malloc(4);
    printf("x: ");
    scanf("%s", s);
    printf("x: %s\n", s);
}
