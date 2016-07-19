#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

void itoa(int n, char s[]);

void itoa(int n, char s[])
{
    static int i = 0;

    if (n / 10)
        itoa(n/10, s);
    else if (n < 0)
        s[i++] = '-';

    s[i++] = abs(n % 10) + '0';

    s[i] = '\0';
}

int main()
{
    char s[255];
    int n = INT_MIN;
    itoa(n, s);
    printf("%d -> %s\n", n, s);
    return 0;
}