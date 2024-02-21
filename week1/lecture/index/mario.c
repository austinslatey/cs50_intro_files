#include <cs50.h>
#include <stdio.h>


int main(void)
{
    // Get grid size
    // int n = getSize();
    int n;
    do
    {
        n = get_int("Size:  ");
    }
    while (n < 1);

    // Print grid of bricks
    for(int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("#");
        }
        printf("\n");
    }

}