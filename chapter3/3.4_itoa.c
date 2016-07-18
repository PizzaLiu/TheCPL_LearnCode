#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

void itoa(int n, char s[]);

void itoa(int n, char s[])
{
    int i, j, sign;
    char c;

    sign = n;
    i = 0;
    do {
        s[i++] = abs(n % 10) + '0';
    } while (n /= 10);
    if ( sign < 0)
        s[i++] = '-';
    //reverse(s);
    --i;
    for (j = 0; j < i/2; ++j) {
        c = s[j];
        s[j] = s[i - j];
        s[i - j] = c;
    }

    s[++i] = '\0';
}

int main()
{
    char s[255];
    int n = INT_MIN;
    itoa(n, s);
    printf("%d -> %s\n", n, s);
    return 0;
}