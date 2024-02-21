#include <cs50.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    string s = get_string("s: ");
    string t = get_string("t: ");

    if (strcmp(s,t) == 0)
    {
        printf("Same\n");
    }

    else if (s != t)
    {
        printf("Different\n");
    }

    printf("%p\n", s);
    printf("%p\n", t);
}