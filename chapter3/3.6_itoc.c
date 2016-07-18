#include <stdio.h>
#include <stdlib.h>

void itoc(int n, char s[], int l);

void itoc(int n, char s[], int l)
{
    int i, j, sign, prefix;
    char c;

    sign = n;
    i = 0;
    do {
        s[i++] = abs(n % 10) + '0';
    } while (n /= 10);
    if ( sign < 0)
        s[i++] = '-';
    //reverse(s);
    if(i < l)
        prefix = l - i;
        for(j = 0; j < prefix; ++j)
            s[i++] = '0';
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
    int n = 1;
    int l = 5;
    itoc(n, s, l);
    printf("%d -> %s\n", n, s);
    return 0;
}