#include <stdio.h>
#include <ctype.h>


int main(int argc, char *argv[])
{
    char *s;
    int i;

    s = argv[0];
    while(s[i++] != '\0')
        if (s[i] >= 'a' && s[i] <= 'z')
            s[i] = toupper(s[i]);
        else
            s[i] = tolower(s[i]);
    
    printf("%s\n", s);
    return 0;
}