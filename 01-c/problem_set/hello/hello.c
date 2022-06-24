#include <stdio.h>
#include <cs50.h>

int main(void)
{
    string name = get_string("What's your name? ");
    printf("hello, %s\n", name);
}

// check50 cs50/problems/2022/x/hello
// style50 hello.c
// submit50 cs50/problems/2022/x/hello