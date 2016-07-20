#include <stdio.h>

#define MAXLINE 1000  /* maximum input line length */

int getlineX(char line[], int maxline);
void copy(char to[], char from[]);

/* print the longest input line */
int main()
{
    int len;    /* current line length */
    int max;    /* maximum length seen so far */
    char line[MAXLINE];     /* current input line */
    char longest[MAXLINE];   /* longest line saved here */

    max = 0;
    while ((len = getlineX(line, MAXLINE)) > 0)
        if(len > max) {
            max = len;
            copy(longest, line);
        }
    if (max > 0) /* there was a line */
        printf("Longest string: %sLength: %d", longest, max);
    return 0;
}

/* getlineX: read a line into s, return length */
int getlineX(char *s, int lim)
{
    int c;
    char *sn;

    for(sn = s+lim; s < sn && (c=getchar())!=EOF && c!='\n'; s++)
        *s = c;
    if(c == '\n') {
        *s= c;
        s++;
    }
    *s = '\0';
    return lim - (sn - s) - 1;
}

/* copy: copy 'from' into 'to'; assume to is big enough */
void copy(char *to, char *from)
{
    while((*to = * from) != '\0') {
        ++to;
        ++from;
    }
}
