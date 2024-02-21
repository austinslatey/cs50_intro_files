#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
    // Check for command line args
    if (argc != 2)
    {
        printf("Usage: ./read infile\n");
        return 1;
    }

    // Create buffer to read into
    // Use fixed-size array instead of an array of pointers
    char buffer[8];

    // Create array to store plate numbers
    // Use a 2D array to store plates
    char plates[8][8];

    FILE *infile = fopen(argv[1], "r");

    int idx = 0;

    // ensure plates runs exactly 8 times. if < 8 plates, handle seperately
    while (fread(buffer, 1, 7, infile) == 7 && idx < 8)
    {
        // Replace '\n' with '\0'
        buffer[6] = '\0';

        // allocate plate number to license array
        // plates[idx] = malloc(strlen(buffer) + 1);

        // copy plate num into array
        strcpy(plates[idx], buffer);
        idx++;
        // Save plate number in array
        // plates[idx] = buffer;
    }

    for (int i = 0; i < 8; i++)
    {
        printf("%s\n", plates[i]);
        // Free memory allocated for each license plate num
        // free(plates[i]);
    }

    // Free allocated memory from license array
    // free(plates);
    return 0;
}
