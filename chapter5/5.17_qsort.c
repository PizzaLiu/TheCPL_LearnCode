#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXLINES 5000    /* max #lines to be sorted */
char *lineptr[MAXLINES]; /* pointers to text lines */
char linestor[MAXLINES];

int readlines(char *lineptr[], char *linestor, int nlines);
void writelines(char *lineptr[], int nlines);

void qsortX(void *lineptr[], int left, int right,
            int (*comp)(void *, void *), int reverse, int unsense, int dirmod);
int numcmp(const char *, const char *);

/* sort input lines */
int main(int argc, char *argv[])
{
    int nlines;         /* number of input lines read */
    int numeric = 0;    /* 1 if numeric sort */
    int reverse = 0;    /* 1 if reverse sort */
    int unsense = 0;    /* 1 if ignore letter case */
    int dirmod = 0;    /* 1 if sort by directory mod */

    for (--argc;argc > 0; --argc) {
        if (!numeric && strcmp(argv[argc], "-n") == 0)
            numeric = 1;
        else if (!reverse && strcmp(argv[argc], "-r") == 0)
            reverse = 1;
        else if (!unsense && strcmp(argv[argc], "-f") == 0)
            unsense = 1;
        else if (!unsense && strcmp(argv[argc], "-f") == 0)
            unsense = 1;
        else if (!dirmod && strcmp(argv[argc], "-d") == 0)
            dirmod = 1;
    }
    if ((nlines = readlines(lineptr, linestor, MAXLINES)) >= 0) {
        qsortX((void**) lineptr, 0, nlines-1,
            (int (*)(void*,void*))(numeric ? numcmp : strcmp), reverse, unsense, dirmod);
        writelines(lineptr, nlines);
        return 0;
    } else {
        printf("input too big to sort\n");
        return 1;
    }
}

/* qsortX: sort v[left]...v[right] into increasing/decreasing order */
void qsortX(void *v[], int left, int right,
        int (*comp)(void *, void *), int reverse, int unsense, int dirmod)
{
    int i, last;
    char s1[MAXLINES], s2[MAXLINES];

    void swap(void *v[], int, int);
    void trans(char *p, const char *s, int tolow, int dirmod);

    if (left >= right)      /* do nothing if array contains */
        return;             /* fewer than two elements */
    swap(v, 0, (left + right)/2);
    last = left;
    if (unsense || dirmod)
        trans(s2, v[left], unsense, dirmod);
    for (i = 0; i <= right; i++) {
        if (unsense || dirmod)
            trans(s1, v[i], unsense, dirmod);
        if ((unsense && ((!reverse && (*comp)(s1, s2) < 0) || (reverse && (*comp)(s1, s2) > 0))) || 
            (!unsense && ((!reverse && (*comp)(v[i], v[left]) < 0) || (reverse && (*comp)(v[i], v[left]) > 0)))
            )
            swap(v, i, ++last);
    }
    swap(v, left, last);
    qsortX(v, left, last - 1, comp, reverse, unsense, dirmod);
    qsortX(v, last+1, right, comp, reverse, unsense, dirmod);

}


#include <stdlib.h>

/* numcmp: compare s1 and s2 mumerically */
int numcmp(const char *s1, const char *s2)
{
    double v1, v2;

    v1 = atof(s1);
    v2 = atof(s2);
    if (v1 < v2)
        return -1;
    else if(v1 > v2)
        return 1;
    else
        return 0;
}

void swap(void *v[], int i, int j)
{
    void *temp;

    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

#define MAXLEN 1000  /* max length of any input line */
#define MAXSTOR 5000
int getlineX(char *, int);

/* readlines: read input lines */
int readlines(char *lineptr[], char *linestor, int maxlines)
{
    int len, nlines;
    char line[MAXLEN];
    char *p = linestor;
    char *linestop = linestor + MAXSTOR;

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
void writelines(char *lineptr[], int nlines)
{
    int i;

    for (i = 0; i < nlines; i++)
        printf("%s\n", lineptr[i]);
}


/* trans: trans letter */
void trans(char *p, const char *s, int tolow, int dirmod)
{
    int i, j;
    char c;
    char ss[MAXLEN];
    char *pp = p;

    for (i = 0, j = 0; (c = s[i]) != '\0'; ++i) {
        if (tolow && (c >= 'A' && c <= 'Z'))
            ss[j++] = c - 'A' + 'a';
        else if (!dirmod || (c == ' ' || isalpha(c) || isdigit(c)))
            ss[j++] = c;
    }
    ss[j] = '\0';
    strcpy(pp, ss);
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
    return lim - (sn - s);
}