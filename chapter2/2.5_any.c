#include <stdio.h>
#include <string.h>

int any(char s1[], char s2[]);

int main()
{
    char s1[] = "squeezeee";
    char s2[] = "ee";

    printf("The offset of \"%s\" first show in \"%s\" is %d", s2, s1, any(s1, s2));
    return 0;
}

int any(char s1[], char s2[])
{
    int i, j, k, len1, len2;

    len1 = strlen(s1);
    len2 = strlen(s2);

    for( i = 0; i < len1; ++i) {
        for( j = 0; j < len2 && i+j < len1 && s1[i+j] == s2[j]; ++j)
            ;
        if(j == len2)
            return i;
    }

    return -1;
}

