#include <cs50.h>
#include <stdio.h>
#include <string.h>

const int BITS_IN_BYTE = 8;

void print_bulb(int bit);

int main(void)
{
    // TODO
    // Ask user for a message
    string message = get_string("Enter a message: ");
    // for loop for each character in string
    for (int i = 0, n = strlen(message); i < n; i++)
    {
        char c = message[i];
        // convert string into a series of 8 bit binary
        for (int j = BITS_IN_BYTE - 1; j >= 0; j--)
        {
            int bit = (c >> j) & 1;
             // print bulb
             print_bulb(bit);
        }
        printf("\n");
    }
}

void print_bulb(int bit)
{
    if (bit == 0)
    {
        // Dark emoji
        printf("\U000026AB");
    }
    else if (bit == 1)
    {
        // Light emoji
        printf("\U0001F7E1");
    }
}
