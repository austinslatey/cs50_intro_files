#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    // single non-negative int cmdline argument called 'k'

    int k;
    // input validation for missing arguments or more than one argument
    if (argc != 2)
    {
        // send error message
        printf("Usage: ./caesar key\n");
        // return from main a value of 1 (error)
        return 1;
    }

    // conver cmdline arg to an integer
    if (argc == 2)
    {
        k = atoi(argv[1]);
    }

    // if any character of the cmdline arg is not a decimal digit
    for (int i = 0; argv[1][i] != '\0'; i++)
    {
        if (!isdigit(argv[1][i]))
        {
            // print "Usage: ./caesar key"
            printf("Usage: ./caesar key\n");
            // return from main a value of 1 (error)
            return 1;
        }
    }

    // prompt user for a string of plaintext
    string plaintext = get_string("plaintext: ");
    // iterate through each character (char) in the string
    printf("ciphertext: ");
    for (int i = 0; plaintext[i] != '\0'; i++)
    {
        char c = plaintext[i];
        // if the char is an alphabetical char
        if (isalpha(c))
        {
            // if the char is lowercase,
            if (islower(c))
            {
                // subtract 97 to get the index from 0-25, then add 'k', mod 26 to get the new index
                // add 97 back to the index to get the ASCII value of the new character
                printf("%c", ((c - 97 + k) % 26) + 97);
            }
            // if char is uppercase
            else
            {
                // subtract 65 to the index from 0-25, then add 'k', mod 26 to get the new index
                // add 65 back to the index to get the ASCII value of the new character
                printf("%c", ((c - 65 + k) % 26) + 65);
            }
        }

        // if the char is not an alphabetical char
        else
        {
            printf("%c", c);
        }
    }
    printf("\n");
    return 0;
}