#include <stdio.h>
#include <string.h>

void escape(char s[], char t[]);
void inscape(char s[], char t[]);

void escape(char s[], char t[])
{
    int i, k, n;

    n = strlen(t);

    for(i = 0, k = 0; i < n; i++, k++)
        switch(t[i]) {
            case '\n':
                s[k] = '\\';
                s[++k] = 'n';
                break;
            case '\t':
                s[k] = '\\';
                s[++k] = 't';
                break;
            default:
                s[k] = t[i];
        }

    s[k] = '\0';
}

void inscape(char s[], char t[])
{
    int i, k, n;

    n = strlen(t);

    for(i = 0, k = 0; i < n; i++, k++)
        switch(t[i]) {
            case '\\':
                if(i == n-1)
                    s[k] = t[i];
                else {
                    if(t[i+1] == 'n') {
                        s[k] = '\n';
                        ++i;
                    } else if(t[i+1] == 't') {
                        s[k] = '\t';
                        ++i;
                    } else
                        s[k] = t[i];
                }
                break;
            default:
                s[k] = t[i];
        }

    s[k] = '\0';
}

int main()
{
    char s[255];
    char t[] = "Hello,\nWorld!";

    escape(s, t);
    printf("%s -> %s\n", t, s);
    inscape(t, s);
    printf("%s -> %s\n", s, t);

    return 0;
}