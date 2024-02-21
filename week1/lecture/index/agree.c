#include <cs50.h>
#include <stdio.h>

int main(void)
{
    char c = get_char("Do you agree? Type upper/lower case ' y or n' ");

    if (c == 'y' || c == 'Y' )
    {
        printf("Agreed\n");
    }
    else if (c == 'n' || c == 'N')
    {
        printf("didnt agree\n");
    }
    else {
        printf("Please type a valid character\n");
    }
}