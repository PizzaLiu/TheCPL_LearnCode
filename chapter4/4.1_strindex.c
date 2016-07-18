#include <stdio.h>


int strindex(char s[], char t[]);

int strindex(char s[], char t[])
{
    int i, j, k, index;

    index = -1;

    for (i = 0; s[i] != '\0'; ++i) {
        for(j = 0, k = i; t[j] != '\0' && s[k] == t[j]; ++j, ++k)
            ;
        if(j > 0 && t[j] == '\0')
            index = i;
    }

    return index;
}

int main()
{
    char s[] = "Hello, lolita.";
    char t[] = "lo";

    printf("strindex(\"%s\", \"%s\") = %d\n", s, t, strindex(s, t));
    return 0;
}