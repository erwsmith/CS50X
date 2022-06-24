#include <cs50.h>
#include <stdio.h>

void draw(int n);

int main(void)
{
    // get height of pyramid
    int height = get_int("Height: ");
    // draw pyramid
    draw(height);
}

void draw(int n)
{
    // If nothing to draw
    if (n <= 0)
    {
        return;
    }
    // RECURSION HERE: draw() function calls itself
    // Draw pyramid of height n - 1
    draw(n - 1);

    // Draw one more row of width n
    for (int i = 0; i < n; i++)
    {
        printf("#");
    }
    printf("\n");
}