#include <cs50.h>
#include <math.h>
#include <stdio.h>

long long card;
int main()
{
    do
    {
        card = get_long_long("Number:");
    }
    while (card == 0);

    // first we check the length
    long long length = (long long) log10((double) card) + 1;
    // printf("%lld\n", card);
    // printf("%lld\n", length);
    if (length != 13 && length != 15 && length != 16)
    {
        printf("INVALID\n");
        return 0;
    }

    // second we check which card it could be
    string OUTPUT = "INVALID";
    // printf("%lld\n", card / 1000000000000000);
    if ((length == 13) && (card / 1000000000000 == 4))
    {
        OUTPUT = "VISA";
    }
    else if ((length == 15) && ((card / 10000000000000 == 34) || (card / 10000000000000 == 37)))
    {
        OUTPUT = "AMEX";
    }
    else if (length == 16)
    {
        if (card / 1000000000000000 == 4)
        {
            // printf("visa baby\n");
            OUTPUT = "VISA";
        }
        else if (card / 100000000000000 >= 51 && card / 100000000000000 <= 55)
        {
            OUTPUT = "MASTERCARD";
        }
    }
    else
    {
        OUTPUT = "INVALID";
    }

    // third we calculate luhn's sum
    long long luhn_sum = 0;
    for (int i = 1; i <= length; i++)
    {
        if (i % 2 == 1)
        {
            luhn_sum = luhn_sum + (card % 10);
            card = card / 10;
        }
        else if (i % 2 == 0)
        {
            long long buffer = 2 * (card % 10);
            luhn_sum = luhn_sum + (buffer % 10) + (buffer / 10);
            card = card / 10;
        }
    }
    // printf("%lld\n", luhn_sum);

    // fourth we output the type
    if (luhn_sum % 10 == 0)
    {
        printf("%s\n", OUTPUT);
        return 0;
    }
    else
    {
        printf("INVALID\n");
        return 0;
    }
}
