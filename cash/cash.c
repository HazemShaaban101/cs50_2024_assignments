#include <cs50.h>
#include <stdio.h>

// function specifiers
int get_cents(void);
int calculate_quarters(int n);
int calculate_dimes(int n);
int calculate_nickels(int n);
int calculate_pennies(int n);

int coins = 0;
int change = 0; // global var so all functions could modify it
int main()
{
    change = get_cents();
    coins = calculate_quarters(change);
    coins += calculate_dimes(change);
    coins += calculate_nickels(change);
    coins += calculate_pennies(change);
    printf("%d\n", coins);
    return 0;
}

// function of calculating all the coins
int get_cents(void)
{
    do
    {
        change = get_int("Change owed:");
    }
    while (change < 0);
    return change;
}

int calculate_quarters(int n)
{
    // calculates nickles by taking the remainder after dividing by 25
    int quarters = n / 25;
    change = n % 25;
    // printf("1: %d   %d\n", quarters, change);
    return quarters;
}

int calculate_dimes(int n)
{
    // calculates nickles by taking the remainder after dividing by 10
    int dimes = n / 10;
    change = n % 10;
    // printf("2: %d   %d\n", dimes, change);
    return dimes;
}

int calculate_nickels(int n)
{
    // calculates nickles by taking the remainder after dividing by 5
    int nickels = n / 5;
    change = n % 5;
    // printf("3: %d   %d\n", nickels, change);
    return nickels;
}

int calculate_pennies(int n)
{
    // calculates nickles by taking the remainder after dividing by 1
    int pennies = n / 1;
    change = n % 1;
    // printf("4: %d   %d\n", pennies, change);
    return pennies;
}