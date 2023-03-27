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
        printf("Usage: reverse input.wav output.wav\n");
        return 1;
    }

    // Open input file for reading
    // Get address of file of the input file
    char *infile = argv[1];
    // Open file & read it
    FILE *inptr = fopen(infile, "rb");
    if (inptr == NULL)
    {
        printf("Input file %s could not be opened\n", infile);
        return 2;
    }

    // Read header
    WAVHEADER header;
    fread(&header, sizeof(WAVHEADER), 1, inptr);

    // Use check_format to ensure WAV format
    if (check_format(header) != 1)
    {
        printf("Not a wave file.\n");
        return 3;
    }
    if (header.audioFormat != 1)
    {
        printf("Not a wave file.\n");
        return 3;
    }

    // Open output file for writing
    char *outfile = argv[2];
    FILE *outptr = fopen(outfile, "wb");
    if (outptr == NULL)
    {
        printf("Could not open %s.\n", outfile);
        return 4;
    }

    // Write header to file
    fwrite(&header, sizeof(WAVHEADER), 1, outptr);

    // Use get_block_size to calculate size of block
    int size = get_block_size(header);

    // Write reversed audio to file
    // Know the starting position
    if (fseek(inptr, size, SEEK_END))
    {
        return 5;
    }
    // Create buffer to store audio
    BYTE buffer[size];
    while (ftell(inptr) - size > sizeof(header))
    {
        if (fseek(inptr, -2 * size, SEEK_CUR))
        {
            return 6;
        }
        fread(buffer, size, 1, inptr);
        fwrite(buffer, size, 1, outptr);
    }

    // Close input & output files
    fclose(inptr);
    fclose(outptr);
}

int check_format(WAVHEADER header)
{
    if (header.format[0] == 'W' && header.format[1] == 'A' && header.format[2] == 'V' && header.format[3] == 'E')
    {
        return 1;
    }
    else return 0;
}

int get_block_size(WAVHEADER header)
{
    // TODO #7
    // The header object gives you channels & bits per sample (you need to divide by bytes)
    int size = header.numChannels * header.bitsPerSample / 8;
    return size;
}