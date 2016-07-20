#include <stdio.h>
#include <string.h>

void reverse(char s[])
{
    static int begin = 0;
    static int end = 0;
    char tmp;

    if(end == 0)
        end = strlen(s) - 1;

    if (begin < end) {
        tmp = s[begin];
        s[begin] = s[end];
        s[end] = tmp;
        begin++;
        end--;
        reverse(s);
    }

    return ;
}

int main()
{
    char s[] = "Hello";

    printf("reverse(\"%s\") = ", s);
    reverse(s);
    printf("\"%s\"\n", s);
    return 0;
}