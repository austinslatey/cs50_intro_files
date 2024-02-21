#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main (void)
{
    // Code goes here
    string name = get_string("What is your name? ");
    int n = strlen(name);
    // while (name[n] != '\0')
    // {
    //     n++;
    // }
    printf("%i\n", n);
}