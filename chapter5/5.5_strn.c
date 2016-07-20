#include <stdio.h>

void strncpyX(char *s, char *t, int n)
{
    while (n-- > 0 && (*s = *t) != '\0') {
        s++;
        t++;
    }

    *s = '\0';
}

void strcatX(char *s, char *t, int n)
{
    while (*s != '\0')
        s++;
    for(; *t != '\0' && n-- > 0; t++, s++)
        *s = *t;
    *s = '\0';
    return ;
}

int strncmpX(char *s, char *t, int n)
{
    for ( ; *s == *t; s++, t++)
        if (*s == '\0' || --n < 0)
            return 0;
    return *s - *t;
}

int main()
{
    char s[] = "Hello";
    char t[] = "world........";
    int n = 5;

    printf("[strncpy] copy pre %d character of \"%s\" to \"%s\" is ", n, t, s);
    strncpyX(s, t, n);
    printf("\"%s\".\n", s);

    char s2[] = "Hello ";
    char t2[] = "world........";
    printf("[strcat] copy pre %d character of \"%s\" to the end of \"%s\" is ", n, t2, s2);
    strcatX(s2, t2, n);
    printf("\"%s\".\n", s2);

    char s3[] = "abc";
    char t3[] = "abde";
    n = 3;
    printf("[strncmp] strncmp(\"%s\", \"%s\", %d) = %d", s3, t3, n, strncmpX(s3, t3, n));
}