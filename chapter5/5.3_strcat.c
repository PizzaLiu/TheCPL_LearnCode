#include <stdio.h>

void strcatX(char *s, char *t)
{
    while (*s != '\0')
        s++;
    for(; *t != '\0'; t++, s++)
        *s = *t;
    *s = '\0';
    return ;
}

int main()
{
    char s[] = "Hello ";
    char t[] = "world.";

    strcatX(s, t);
    printf("%s\n", s);
    return 0;
}