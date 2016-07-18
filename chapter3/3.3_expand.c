#include <stdio.h>
#include <string.h>

void expand(char s1[], char s2[]);

void expand(char s1[], char s2[])
{
    int n, i, j, k, state;
    char c, begin, end;

    begin = '\0';
    end = '\0';
    state = 0;

    n = strlen(s1);

    for(i = 0, j = 0; i < n; ++i) {
        c = s1[i];
        if(c == '-') {
            if(i > 0) {
                if(i == n -2) {
                    state = 2;
                } else
                    state = 1;
                begin = s1[i-1];
                --j;
            } else
                s2[j++] = c;
        } else if(state == 1 && c != '-') {
            end = c;
            state = 2;
        } else if(state == 2 && c != '-') {
            if(end == '\0') end = c - 1;
            for(k = begin; k <= end; ++k)
                s2[j++] = k;
            s2[j++] = c;
            begin = '\0';
            end = '\0';
            state = 0;
        } else
            s2[j++] = c;
    }

    s2[j] = '\0';
}

int main()
{
    char s1[] = "-a-z0-9Qute!b-c";
    char s2[5536];

    expand(s1, s2);
    printf("%s -> %s\n", s1, s2);
    return 0;
}

