#include <cs50.h>
#include <stdio.h>


int main(void)
{
    // prompt user for height
    int height;
    do
    {
        height = get_int("Size:  ");
    }


    // If height is less than or greater than 8(or not an int) go back to step 1
    while (height < 1 || height > 8);

    // iterate through num to create pyramid
    for (int i = 0; i < height; i++)
    {
        // print the spaces
        for (int j = 0; j < height - i - 1; j++)
        {
            printf(" ");
        }

        // print the left hashes
        for (int j = 0; j <= i; j++)
        {
            printf("#");
        }

        // Print gap
        printf("  ");

        // print right pyramid
        for (int j = 0; j <= i; j++)
        {
            printf("#");
        }

        // new line
        printf("\n");
    }
}