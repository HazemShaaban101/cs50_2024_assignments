#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

// global variables
int letters = 0;
int words = 1;
int sentences = 0;

int main(void)
{
    // prompt user for input
    char *paragraph = get_string( "Text:");
    // calculate string length
    int length = (int) strlen(paragraph);

    // loop for length of paragraph
    for (int i = 0; i < length; i++)
    {
        // check if its a letter
        if ((paragraph[i] >= 65 && paragraph[i] <= 90) || (paragraph[i] >= 97 && paragraph[i] <= 122))
        {
            letters++;
        }
            // check if its a word
        else if (paragraph[i] == 32)
        {
            words++;
        }
            // check if its a sentence
        else if (paragraph[i] == 46 || paragraph[i] == 33 || paragraph[i] == 63)
        {
            sentences++;
        }
    }
    // calculate index components and then index, then round it to nearest int
    float L = (float) letters * 100 / (float) words;
    float S = (float) sentences * 100 / (float) words;
    int index = (int) round((0.0588 * L - 0.296 * S - 15.8));
    // printf("%d letters\n%d words\n%d sentences\nindex = %d\n", letters, words, sentences, index);
    // print output based on index
    if (index < 1)
    {
        printf("Before Grade 1\n");
        return 0;
    }
    else if (index > 16)
    {
        printf("Grade 16+\n");
        return 0;
    }
    else
    {
        printf("Grade %d\n", index);
        return 0;
    }
}
