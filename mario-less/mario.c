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

    for (int counter = 1; counter <= n; counter++)
    {
        // print spaces before the hashes equal to height minus the line number
        printf("%.*s", n - counter, "        ");
        // print hashes equal to line number
        printf("%.*s\n", counter, "########");
    }
    return 0;
}
