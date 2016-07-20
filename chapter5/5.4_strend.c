#include <stdio.h>

int strend(char *s, char *t)
{
    int tn = 0;

    while (*t != '\0') {
        t++;
        tn++;
    }

    while (*s != '\0')
        s++;

    while (*s == *t && tn-- > 0) {
        s--;
        t--;
    }

    if (tn == -1)
        return 1;
    return 0;
}

int main()
{
    char s[] = "Hello world";
    char t[] = "world";

    printf("is \"%s\" in the tail of \"%s\" : %d\n", t, s, strend(s, t));
}