#include <stdio.h>

#define MAXLINE 1000  /* maximum input line length */
#define LIMIT 80      /* limit minimum to print */

int getlineX(char line[], int maxline);

/* print the limit minimum input line */
int main()
{
    int len;    /* current line length */
    char line[MAXLINE];     /* current input line */

    while ((len = getlineX(line, MAXLINE)) > 0)
        if(len > LIMIT) {
            printf("%s", line);
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

