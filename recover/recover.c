#include <stdio.h>
#include <stdint.h>

#define BLOCK 512
 
int main(int argc, char *argv[])
{
    // check number of arguments, they have to be specifically two
    if (argc != 2)
    {
        printf("Usage: ./recover <input file>\n");
        return 1;
    }

    // open input file, if no input file exists print out error
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("couldn't open input file\n");
        return 1;
    }

    // define the output file pointer
    FILE *output = NULL;
    //read bytes until EOF
    uint8_t buffer[BLOCK];
    int file_counter = 0;
    char file_name[11];
    while (fread(buffer, sizeof(uint8_t), BLOCK, input))
    {
        // if first 4 bytes are of the standard image bytes
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && buffer[3] >= 0xe0)
        {
            // if an output file is open
            if (output != NULL)
            {
                // close the output file
                fclose(output);
            }
            // open a new output file and name it a different name than the last one
            sprintf(file_name, "%03d.jpg", file_counter++);
            printf("%s\n", file_name);
            output = fopen(file_name, "w");
            if (output == NULL)
            {
                fclose(input);
                fclose(output);
                printf("couldn't open output file\n");
                return -4;
            }
        }

        // write the block to the open file
        // without this if condition the code crashes, because without it, we assume that the first pic is at first
        // block of memory, if it's not located on the first block though, the code will be writing to the initial NULL
        // address which the output pointer is initialized to
        if (output != NULL)
        {
            // if the number of blocks wrote to output file isnt equal to block size, close files, and print out error
            if (fwrite(buffer, sizeof(uint8_t), BLOCK, output) != BLOCK)
            {
                fclose(input);
                fclose(output);
                printf("unknown error printing into file\nEXITING......\n");
                return -3;
            }
        }
    }

    // close files before terminating the program
    fclose(input);
    fclose(output);
}