#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int convert(string input);

int main(void)
{
    string input = get_string("Enter a positive integer: ");

    for (int i = 0, n = strlen(input); i < n; i++)
    {
        if (!isdigit(input[i]))
        {
            printf("Invalid Input!\n");
            return 1;
        }
    }

    // Convert string to int
    printf("%i\n", convert(input));
}

int convert(string input)
{
    // TODO
    // start with the last char and convert it to an int
    // shorten the string, removing the last char
    // recursively call convert using the shortened string as input, where the next char will be processed

    // base
    if (strlen(input) == 0)
    {
        return 0;
    }
    // recursive step
    else
    {
        int last_digit = atoi(&input[strlen(input) - 1]);
        input[strlen(input) - 1] = '\0';
        return convert(input) * 10 + last_digit;

    }

}