#include <cs50.h>
#include <stdio.h>

int main()
{
    int n = 0;
    do
    {
        // get user input
        n = get_int("Height:");
    }
    while (n < 1 || n > 8);

    // loop for printing output
    for (int i = 1; i <= n; i++)
    {
        // print the space before the hash mark
        printf("%.*s", n - i, "        ");
        // print the hashes equal to line number
        printf("%.*s  ", i, "########");
        // print reversed hashes, we dont need space after, just a new line
        printf("%.*s\n", i, "########");
    }
}
