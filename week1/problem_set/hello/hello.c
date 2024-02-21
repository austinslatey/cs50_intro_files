#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Ask for username and print to the console
    string first = get_string("Whats your name? ");
    printf("Hello, %s\n", first);
}