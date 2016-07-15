#include <stdio.h>
#include <math.h>

int htoi(char s[], int len);

int main()
{
    char h[] = "0x1A";

    printf("%s: %d\n", h, htoi(h, 4));
    return 0;
}

int htoi(char s[], int len)
{
    int i, j, n, p;
    char c;

    i = 0;
    if ( len > 2 && s[i] == '0')
        i = 2;

    p = 0;
    j = len - i - 1;
    for (; i < len; ++i, --j) {
        c = s[i];
        n = 0;
        if (c >= '0' && c <= '9')
            n = c - '0';
        if (c >= 'a' && c <= 'f')
            n = c - 'a' + 11;
        if (c >= 'A' && c <= 'F')
            n = c - 'A' + 11;
        p = p + n * pow(16, j);
    }

    return p;
}