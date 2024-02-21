#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define BLOCK_SIZE 512
typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    // exactly one command-line argument
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }

    // open forensic image
    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        // if forensic image != true
        printf("Could not open %s.\n", argv[1]);
        // return 1 with error message
        return 1;
    }

    // Read the forensic image file and recover the JPEG files
    BYTE buffer[BLOCK_SIZE];
    FILE *jpeg = NULL;
    int jpeg_count = 0;
    char filename[10];

    int max_jpeg_files = 50;

    // Recover JPEG files
    while (fread(buffer, 1, BLOCK_SIZE, file) == BLOCK_SIZE)
    {
        // check for start of a new JPEG
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            if (jpeg != NULL)
            {
                fclose(jpeg);
                jpeg = NULL;
            }

            sprintf(filename, "%03i.jpg", jpeg_count++);
            jpeg = fopen(filename, "w");
            if (jpeg == NULL)
            {
                fclose(file);
                printf("Could not create %s\n", filename);
                return 1;
            }

            fwrite(buffer, 1, BLOCK_SIZE, jpeg);
        }
        else
        {
            if (jpeg != NULL)
            {
                fwrite(buffer, 1, BLOCK_SIZE, jpeg);
            }
        }
    }

    // Close the current JPEG file
    if (jpeg != NULL)
    {
        fclose(jpeg);
        jpeg = NULL;
    }

    // Close the forensic image file
    fclose(file);
    return 0;
}