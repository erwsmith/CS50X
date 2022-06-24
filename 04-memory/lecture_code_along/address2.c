#include <stdio.h>
#include <cs50.h>

int main(void)
{
    string s = "HI!";
    char *p = &s[0];

    // p equals s
    // the address of the first character in s
    // is equal to the address of s
    printf("p %p\n", p);
    printf("s %p\n", s);
    printf("s0 %p\n", &s[0]);
    printf("s1 %p\n", &s[1]);
    printf("s2 %p\n", &s[2]);
    printf("s3 %p\n", &s[3]);
}