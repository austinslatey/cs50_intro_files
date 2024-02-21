#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "wav.h"

int check_format(WAVHEADER header);
int get_block_size(WAVHEADER header);

int main(int argc, char *argv[])
{
    // Ensure proper usage
    if (argc != 3)
    {
        printf("Usage: ./reverse input.wav output.wav\n");
        return 1;
    }

    // Open input file for reading
    FILE *input_file = fopen(argv[1], "rb");
    if (input_file == NULL)
    {
        printf("Can't open the input file!\n");
        return 1;
    }

    // Read header
    WAVHEADER header;
    if (fread(&header, sizeof(WAVHEADER), 1, input_file) != 1)
    {
        printf("Can't read header from input file!\n");
        fclose(input_file);
        return 1;
    }

    // Use check_format to ensure WAV format
    if (!check_format(header))
    {
        printf("Input file is not in WAV format!\n");
        fclose(input_file);
        return 1;
    }

    // Open output file for writing
    FILE *output_file = fopen(argv[2], "wb");
    if (output_file == NULL)
    {
        printf("Can't open the output file!\n");
        fclose(input_file);
        return 1;
    }

    // Write header to file
    if (fwrite(&header, sizeof(WAVHEADER), 1, output_file) != 1)
    {
        printf("Error writing header to output file\n");
        fclose(input_file);
        fclose(output_file);
        return 1;
    }

    // Use get_block_size to calculate size of block
    int block_size = get_block_size(header);

    //  TODO #8 Write reversed audio to file
    // calculate the number of audio blocks in the file
    fseek(input_file, 0, SEEK_END);
    long audio_size = ftell(input_file) - sizeof(WAVHEADER);
    int num_blocks = audio_size / block_size;

    // move the input file pointer back to the beginning of audio data
    fseek(input_file, sizeof(WAVHEADER), SEEK_SET);

    // create array to store audio blocks
    uint8_t *audio_blocks = (uint8_t *)malloc(block_size * num_blocks);
    if (audio_blocks == NULL)
    {
        printf("Memory allocation failed\n");
        fclose(input_file);
        fclose(output_file);
        return 1;

    }

    // read audio in reverse order
    for (int i = num_blocks -1; i >= 0; i--)
    {
        // Move the input file pointer to the correct position
        fseek(input_file, -block_size, SEEK_END);

        if (fread(&audio_blocks[i * block_size], 1, block_size, input_file) != block_size)
        {
            printf("Error reading audio :/\n");
            free(audio_blocks);
            fclose(input_file);
            fclose(output_file);
            return 1;
        }
    }
    for (int i =0; i < num_blocks; i++)
    {
        // determine the postition of the first channel of the current audio blocks
        int block_start = i * block_size;

        // Write the audio block to the output file
        if (fwrite(&audio_blocks[block_start], 1, block_size, output_file) != block_size)
        {
            printf("Error writing revered audio to output file :/\n");
            free(audio_blocks);
            fclose(input_file);
            fclose(output_file);
            return 1;
        }
    }
}

int check_format(WAVHEADER header)
{
    // Implement WAV format check
    if (header.format[0] == 'W' && header.format[1] == 'A' && header.format[2] == 'V' && header.format[3] == 'E')
    {
        // Valid WAV
        return 1;
    }
    // Invalid WAV
    return 0;
}

int get_block_size(WAVHEADER header)
{
    // Calculate block size
    int bytesPerSample = header.bitsPerSample / 8;
    int block_size = header.numChannels * bytesPerSample;
    if (header.blockAlign > 0)
    {
        // stereo audio
        block_size = header.blockAlign;
    }
    return block_size;
}