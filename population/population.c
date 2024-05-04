#include <cs50.h>
#include <stdio.h>

int main()
{
    // prompt user for starting size
    int n = get_int("Start size: ");
    // if input is invalid, keep asking till it is
    while (n < 9)
    {
        n = get_int("Start size: ");
    }

    // prompt user for final size
    int final = get_int("End size: ");
    // if size is invalid, keep asking till it is
    while (final < n)
    {
        final = get_int("End size: ");
    }
    int years = 0;
    // keep counting the years until start size reaches end size
    while (n < final)
    {
        n = n + (n / 3) - (n / 4);
        years++;
    }
    // print out amount of years
    printf("Years: %d\n", years);
}
