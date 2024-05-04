#include <cs50.h>
#include <stdio.h>
#include<string.h>
#include <ctype.h>
#include <stdlib.h>
// damn boy that's a lot of libraries
bool only_digits(string s);

int main(int argc, char *argv[])
{
    // check argument count
    if (argc != 2 || only_digits(argv[1]))
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    int key = strtol(argv[1], NULL, 0);
    // prompt user for input text
    char *input = get_string("plaintext:  ");
    int length = (int) strlen(input);

    // print out output text
    printf("ciphertext: ");
    for (int i = 0; i < length; i++)
    {
        if (input[i] >= 65 && input[i] <= 90)
        {
            // upper case
            printf("%c", 65 + ((input[i] - 65 + key) % 26));
        }
        else if (input[i] >= 97 && input[i] <= 122)
        {
            // Lower
            printf("%c", 97 + ((input[i] - 97 + key) % 26));
        }
        else
        {
            // not a letter
            printf("%c", input[i]);
        }
    }
    printf("\n");
}

// checks if argument 1 is only numbers, if it is, return 0, otherwise return 1
bool only_digits(string s)
{
    int length = (int) strlen(s);
    for (int i = 0; i < length; i++)
    {
        if (!isdigit((s[i])))
        {
            return 1;
        }
    }
    return 0;
}