#include <stdio.h>

#define MAXLINE 1000  /* maximum input line length */

int getlineX(void);
void copy(void);
int max;
char longest[MAXLINE], line[MAXLINE];

/* print the longest input line; speciaalized version */
int main()
{
    int len;    /* current line length */
    extern int max;    /* maximum length seen so far */
    extern char longest[];   /* longest line saved here */

    max = 0;
    while ((len = getlineX()) > 0)
        if(len > max) {
            max = len;
            copy();
        }
    if (max > 0) /* there was a line */
        printf("%s", longest);
    return 0;
}

/* getlineX: specialized version */
int getlineX(void)
{
    int c, i;
    extern char line[];

    for (i = 0; i < MAXLINE-1 && (c=getchar())!=EOF && c!='\n'; ++i)
        line[i] = c;
    if (c == '\n') {
        line[i] = c;
        ++i;
    }
    line[i] = '\0';
    return i;
}

/* copy: specialized version */
void copy(void)
{
    int i;
    extern char line[], longest[];

    i = 0;
    while((longest[i] = line[i]) != '\0')
        ++i;
}
