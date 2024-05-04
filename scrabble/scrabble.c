#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int compute_score(char *);
int scores[26] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int main()
{
    // prompt for players words
    char *player1 = get_string("Player 1:");
    char *player2 = get_string("Player 2:");

    // calculate scores for each player
    int score1 = compute_score(player1);
    int score2 = compute_score(player2);

    // output winner based on biggest score
    if (score1 > score2)
    {
        printf("Player 1 wins!\n");
        return 0;
    }
    else if (score1 < score2)
    {
        printf("Player 2 wins!\n");
        return 0;
    }
    else
    {
        printf("Tie!\n");
    }
}

int compute_score(char *input)
{
    int output = 0;

    // calculate length of word
    int length = (int) strlen(input);

    // loop for length of word
    for (int i = 0; i < length; i++)
    {
        // convert UPPERCASE letters into lowercase
        input[i] = (char) tolower(input[i]);

        // check if character is an english letter or not
        if (input[i] >= 97 && input[i] <= 122)
        {
            // if it is a letter, increment score by corresponding letter score
            output += scores[input[i] - 97];
        }
    }
    return output;
}