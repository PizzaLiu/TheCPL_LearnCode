#include <stdio.h>
#include <string.h>

void squeeze(char s1[], char s2[]);

int main()
{
    char s1[] = "squeezeee";
    char s2[] = "ee";

    printf("Remove \"%s\" from \"%s\" is ", s2, s1);
    squeeze(s1, s2);
    return 0;
}


void squeeze(char s1[], char s2[])
{
    int i, j, k, len1, len2;

    len1 = strlen(s1);
    len2 = strlen(s2);

    char s[len1+1];
    k = 0;
    for( i = 0; i < len1; ++i) {
        for( j = 0; j < len2 && i+j < len1 && s1[i+j] == s2[j]; ++j)
            ;
        if(j != len2)
            s[k++] = s1[i];
        else
            i += j - 1;
    }

    s[k] = '\0';
    printf("\"%s\"\n", s);
    //s1 = s;
}