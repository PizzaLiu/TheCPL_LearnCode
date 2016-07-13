#include <stdio.h>

#define MAXLINE 1000  /* maximum input line length */

int getlineX(char line[], int maxline);
int filtlineX(char s[], int len);

int main()
{
    int len;    /* current line length */
    char line[MAXLINE];     /* current input line */

    while ((len = getlineX(line, MAXLINE)) > 0) {
        len = filtlineX(line, len);
        if(len > 0) {
            printf("%s\n", line);
        }
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

/* filtlineX: delete white space and tab in the end of line
             and remove total white space line */
int filtlineX(char s[], int len)
{
    int i;
    for (i = len - 2; i >= 0; --i) {
        if(s[i] == ' ' || s[i] == '\t')
            ;
        else
            break;
    }

    s[++i] = '\0';
    return i;
}