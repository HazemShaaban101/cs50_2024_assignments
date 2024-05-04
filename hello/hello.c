#include <cs50.h>
#include <stdio.h>

int main()
{
    // asks for your name
    string name = get_string("What's your name? ");
    // prints hello, name
    printf("Hello, %s\n", name);
    return 0;
}