#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINES 5000    /* max #lines to be sorted */
#define MAXLEN 1000  /* max length of any input line */

char *lineptr[MAXLINES];  /* pointers to text lines */
char linestor[MAXLINES];

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
    return lim - (sn - s);
}

/* readlines: read input lines */
int readlines(char *lineptr[], char *linestor, int maxlines)
{
    int len, nlines;
    char line[MAXLEN];
    char *p = linestor;
    char *linestop = linestor + MAXLINES;

    nlines = 0;
    while ((len = getlineX(line, MAXLEN)) > 0)
        if (nlines >= maxlines || p+len > linestop)
            return -1;
        else {
            line[len-1] = '\0';  /* delete newline */
            strcpy(p, line);
            lineptr[nlines++] = p;
            p += len;
        }
    return nlines;
}

/* writelines: write output lines */
void writelines(char *lineptr[], int begin, int end)
{
    int i;

    for (i = begin; i < end; i++)
        printf("%s\n", lineptr[i]);
}



int main(int argc, char *argv[])
{
    int n = 10;
    int nlines;  /* number of input lines read */

    if (argc == 2) 
        n = abs(atoi(argv[1]));

    if((nlines = readlines(lineptr, linestor, MAXLINES)) >= 0) {
        writelines(lineptr, nlines - n, nlines);
        return 0;
    } else {
        printf("error: input too big to store\n");
        return 1;
    }

    return 0;
}