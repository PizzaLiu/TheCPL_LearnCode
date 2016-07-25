#include <stdio.h>

#define MAX_LEN 255
#define HAS_WSP 1
#define NO_WSP 0
#define TAB_LEN 4

void entab(char s[], int len);
void detab(char s[], int len);
int getlineX(char s[]);
char ss[MAX_LEN];
int sslen = 0;
int flag = 4;

int main(int argc, char *argv[])
{
    int len;
    char line[MAX_LEN];

    if (argc > 1)
        flag = argv[2][0];

    while((len = getlineX(line))> 0) {
        entab(line, len);
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

/* entab: transform white space to tab */
void entab(char s[], int len)
{
    int i, j, state;
    extern char ss[MAX_LEN];
    extern int sslen;

    for(j = 0; j < sslen; ++j)
        ss[j] = '\0';

    state = NO_WSP;
    for(i = 0, j = -1; i < len; ++i) {
        if(s[i] == ' ') {
            state = HAS_WSP;
        } else {
            if(state == HAS_WSP)
                ss[++j] = '\t';
            ss[++j] = s[i];
            state = NO_WSP;
        }
    }
    sslen = ++j;
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
            if (nw < flag)
                n = 2*flag - nw;
            else if (nw == flag)
                n = flag;
            else if (nw%flag > 0)
                n = flag - nw%flag;
            else
                n = 2*flag;
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
