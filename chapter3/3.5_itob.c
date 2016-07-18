#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

void itob(int n, char s[], int b);

void itob(int n, char s[], int b)
{
    int i, j, sign;
    char symbols[] = "0123456789ABCDEFGHIJKLMNOPQRST";
    char c;

    sign = n;
    i = 0;
    do {
        s[i++] = symbols[abs(n % b)];
    } while (n /= b);
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
    int b = 2;
    itob(n, s, b);
    printf("itob(%d, s[], %d) -> %s\n", n, b, s);
    return 0;
}