#include <stdio.h>

#define LINE_MAX_LEN  80
#define ARR_MAX  255


int getlineX(char s[]);
void splitline(char s[], int len);
char ss[ARR_MAX];
int sslen = 0;

int main()
{
    int len;
    char line[ARR_MAX];

    while((len = getlineX(line))> 0) {
        splitline(line, len);
        printf("%s\n", ss);
    }
    return 0;
}


/* getlineX: read a line into s, return length */
int getlineX(char s[])
{
    int c, i;

    for(i = 0; i < ARR_MAX-1 && (c=getchar())!=EOF && c!='\n'; ++i)
        s[i] = c;
    if(c == '\n') {
        s[i] = c;
        ++i;
    }
    s[i] = '\0';
    return i;
}

/* splitline: splite long line to multi lines */
void splitline(char s[], int len)
{
    int i, j, nw;
    extern char ss[ARR_MAX];
    extern int sslen;

    for(j = 0; j < sslen; ++j)
        ss[j] = '\0';

    nw = 0;
    for (i = 0, j = -1; i < len; ++i) {
        ss[++j] = s[i];
        if(nw >= LINE_MAX_LEN && s[i] != ' ' && s[i] != '\t') {
            ss[++j] = '\n';
            nw = 0;
        } else {
            if(s[i] == '\t')
                nw += 4;
            else
                ++nw;
        }
    }
    sslen = ++j;
}
