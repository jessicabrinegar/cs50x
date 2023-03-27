// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    float factor = atof(argv[3]);

    // TODO: Copy header from input file to output file
    // declaration of array called header, with a type for unsigned 8 bit integers.
    // we want # of bytes that matches the header size
    uint8_t header[HEADER_SIZE];
    // read buffer from input file into the header variables (into memory)
    // write contents of header variable to output file
    fread(header, HEADER_SIZE, 1, input);
    fwrite(header, HEADER_SIZE, 1, output);

    // TODO: Read samples from input file and write updated data to output file
    // buffer needs to store enough data for a 2 byte sample
    int16_t buffer;
    // pass in address of buffer so it reads the data to that address
    // will repeatedly read the samples until it reaches the end of the file (fread will return 0)
    while (fread(&buffer, sizeof(int16_t), 1, input))
    {
        // update volume
        buffer *= factor;
        // write updated data (from buffer) to the output file
        fwrite(&buffer, sizeof(int16_t), 1, output);
    }
    // Close files
    fclose(input);
    fclose(output);
}