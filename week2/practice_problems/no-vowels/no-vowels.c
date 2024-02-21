#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// import string replace
string replace(string input);

int main(int argc, string argv[])
{
    // Write a function to replace vowels with numbers
    // Create input validation
    if (argc != 2)
    {
        printf("Usage: %s word\n", argv[0]);
        return 1;
    }

    // Get practice with strings

    // Get input string
    string input = argv[1];

    // replace vowels with numbers
    string output = replace(input);

    // print output
    printf("%s\n", output);

    return 0;

    // Get practice with command line
}

string replace(string input)
{
    // allocate memory for output
    string output = malloc(strlen(input) + 1);

    // copy input to output
    strcpy(output, input);

    // replace vowels with numbers
    for (int i = 0, n = strlen(output); i < n; i++)
    {
        // Get practice with switch
        switch (output[i])
        {
            case 'a':
            case 'A':
                output[i] = '6';
                break;
            case 'e':
            case 'E':
                output[i] = '3';
                break;
            case 'i':
            case 'I':
                output[i] = '1';
                break;
            case 'o':
            case 'O':
                output[i] = '0';
                break;
            default:
                // Do nothing
                break;
        }
    }

    return output;
}
