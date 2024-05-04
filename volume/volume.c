// this program modifies volume of a wav file
// this is written entirely by : Hazem Shaaban Bakry
// email: 7azemsh3baan@gmail.com
// phone : +201023445907
//==========================================================//

// include libraries
#include <stdio.h>
#include<stdlib.h>
#include <stdint.h>

// function headers
int copy_header(FILE *input, FILE *output);
int change_sample(FILE *input, FILE *output, float factor);

// main body
int main(int argc, char *argv[])
{
    // check if input arguments are equal to input args needed to execute the program
    if (argc != 4)
    {
        printf("Usage: ./volume <input file> <output file> <factor of amplification>\n");
        return -1;
    }
    // open input file, if input file is NULL it means we couldn't open the file
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("couldn't open input file\n");
        return -2;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("couldn't open output file\n");
        return -3;
    }
    // factor of amplification, inputed as string, and converted to float
    float factor = (float) atof(argv[3]);

    if (copy_header(input, output))
    {
        printf("couldn't read header\n");
        return -4;
    }

    change_sample(input, output, factor);




    // Close files
    fclose(input);
    fclose(output);
}

// this function will read input header and save it to a buffer of size 44 bytes
// then will write the buffer to the output file as long as it actually reads 44 bytes
// the reason why we didnt use fread and fwrite is because we want to make sure we read exactly 44 bytes
int copy_header(FILE *input, FILE *output)
{
    uint8_t *buffer = malloc(sizeof(uint8_t) * 44);
    if (fread(buffer, sizeof(uint8_t), 44, input) == 44)
    {
        fwrite(buffer, sizeof(uint8_t), 44, output);
        return 0;
    }
    printf("couldn't read entire buffer\n");
    return 1;
}

// this function will read sample and save it to buffer of size 16 bits
// then multiply the sample by the factor, then write the new sample to the output
int change_sample(FILE *input, FILE *output, float factor)
{
    int16_t buffer = 0;
    while ((fread(&buffer, sizeof(int16_t), 1, input)) != 0)
    {
        buffer  = (int16_t)((float) buffer * factor);

        fwrite(&buffer, sizeof(int16_t), 1, output);
    }
    return 0;
}

