#include <stdio.h>

#define LINE_MAX_LEN  80
#define ARR_MAX  255
#define IN_COMM 1
#define OUT_COMM 0


int getlineX(char s[]);
void removecom(char s[], int len);
char ss[ARR_MAX];
int sslen = 0;

int main()
{
    int len;
    char line[ARR_MAX];

    while((len = getlineX(line))> 0) {
        removecom(line, len);
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

/* removecom: remove comments in c lang */
void removecom(char s[], int len)
{
    int i, j, state;
    extern char ss[ARR_MAX];
    extern int sslen;

    state = OUT_COMM;

    for(j = 0; j < sslen; ++j)
        ss[j] = '\0';

    for (i = 0, j = -1; i < len; ++i) {
        if(state == OUT_COMM && i < len - 1 && s[i] == '/' && s[i+1] == '*') {
            state = IN_COMM;
            ++i;
        } else if(state == OUT_COMM)
            ss[++j] = s[i];
        else if(state == IN_COMM && i < len - 1 && s[i] == '*' && s[i+1] == '/') {
            state = OUT_COMM;
            ++i;
        }
    }
    sslen = ++j;
}
