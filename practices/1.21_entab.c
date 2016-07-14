#include <stdio.h>

#define MAX_LEN 255
#define HAS_WSP 1
#define NO_WSP 0

void entab(char s[], int len);
int getlineX(char s[]);
char ss[MAX_LEN];
int sslen = 0;

int main()
{
    int len;
    char line[MAX_LEN];

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
