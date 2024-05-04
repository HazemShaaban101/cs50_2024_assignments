#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char *argv[])
{
    // check if input arguments aren't 1
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    // checks if key length isn't 26
    int key_length = (int) strlen(argv[1]);
    if (key_length != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    for (int i = 0; i < key_length; i++)
    {
        // make the key into upper case
        argv[1][i] = (char) toupper(argv[1][i]);
    }

    // checks key to make sure it's valid
    for (int i = 0; i < key_length; i++)
    {
        // check if all letters are alphabet
        if (!isalpha(argv[1][i]))
        {
            printf("INVALID KEY\n");
            return 1;
        }
        // checks if there are repeated letters in key
        for (int j = i + 1; j < key_length; j++)
        {
            if (argv[1][i] == argv[1][j])
            {
                printf("INVALID KEY\n");
                return 1;
            }
        }
    }

    // right now key is valid, we then ask for plain text input
    char *plain = get_string("plaintext:");
    printf("ciphertext:");

    int plain_length = (int) strlen(plain);
    for (int i = 0; i < plain_length; i++)
    {
        if (isalpha(plain[i]))
        {
            if (isupper(plain[i]))
            {
                printf("%c", argv[1][plain[i] - 65]);
            }
            else
            {
                printf("%c", tolower(argv[1][plain[i] - 97]));
            }
        }
        else
        {
            printf("%c", plain[i]);
        }
    }
    printf("\n");
    return 0;
}
