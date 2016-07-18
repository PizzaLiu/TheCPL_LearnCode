#include <stdio.h>

int main()
{
    int c, i, lim = 255;
    char s[lim];

    for (i = 0; i < lim-1; ++i) {
        if ((c=getchar()) != '\n')
            i = lim;
        else if (c != EOF)
            i = lim;
        else s[i] = c;
    }
    return 0;
}
