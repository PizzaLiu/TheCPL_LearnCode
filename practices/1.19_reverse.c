#include <stdio.h>

#define MAXLINE 1000  /* maximum input line length */

int getlineX(char line[], int maxline);
void reverse(char s[], int len);

int main()
{
    int len;
    char line[MAXLINE];

    while((len = getlineX(line, MAXLINE)) > 0) {
        reverse(line, len);
        printf("%s\n", line);
    }
    return 0;
}

/* getlineX: read a line into s, return length */
int getlineX(char s[], int lim)
{
    int c, i;

    for(i = 0; i < lim-1 && (c=getchar())!=EOF && c!='\n'; ++i)
        s[i] = c;
    if(c == '\n') {
        s[i] = c;
        ++i;
    }
    s[i] = '\0';
    return i;
}



void reverse(char s[], int len)
{
    int mid, i;
    char c;

    mid = len / 2;

    for (i = 0; i < mid; ++i) {
        c = s[len-1-i];
        s[len-1-i] = s[i];
        s[i] = c;
    }
}