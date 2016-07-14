#include <stdio.h>

#define TAB_LEN 4
#define MAX_LEN 255

void detab(char s[], int len);
int getlineX(char s[]);
char ss[MAX_LEN];
int sslen = 0;

int main()
{
    int len;
    char line[MAX_LEN];

    while((len = getlineX(line))> 0) {
        detab(line, len);
        printf("%s\n", ss);
    }
}

/* getlineX: read a line into s, return length */
int getlineX(char s[])
{
    int c, i;

    for(i = 0; i < MAX_LEN-1 && (c=getchar())!=EOF && c!='\n'; ++i)
        s[i] = c;
    if(c == '\n') {
        s[i] = c;
        ++i;
    }
    s[i] = '\0';
    return i;
}


/* detab: transform tab to white space */
void detab(char s[], int len)
{
    int i, j, k, n, nw;
    extern char ss[MAX_LEN];
    extern int sslen;

    for(j = 0; j < sslen; ++j)
        ss[j] = '\0';

    for(i = 0, j = 0, nw = 0; i < len && j < MAX_LEN - 1; ++i, ++j) {
        if(s[i] == '\t') {
            if (nw < TAB_LEN)
                n = 2*TAB_LEN - nw;
            else if (nw == TAB_LEN)
                n = TAB_LEN;
            else if (nw%TAB_LEN > 0)
                n = TAB_LEN - nw%TAB_LEN;
            else
                n = 2*TAB_LEN;
            for (k = 0; k < n; ++k, ++j) {
                ss[j] = ' ';
            }
            --j;
            nw = 0;
        } else {
            ss[j] = s[i];
            ++nw;
        }
    }
    sslen = j;
}