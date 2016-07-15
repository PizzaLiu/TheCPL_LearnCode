#include <stdio.h>

char lower(char c);

int main()
{
    char c = 'P';

    printf("lower(%c) = %c\n", c, lower(c));
    return 0;
}

char lower(char c)
{
    return c >= 'a' && c <= 'z' ? c : c + ('a' - 'A');
}