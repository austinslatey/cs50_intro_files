#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main (int argc, string argv[])
{
    // Code goes here
    // string name = get_string("Whats your name cutie? ");
    // prompt by ./greet {name}
    if (argc == 2)
    {
        printf("Hello, %s\n", argv[1]);
    }
    else 
    {
        printf("foo, bar\n");
    }

}