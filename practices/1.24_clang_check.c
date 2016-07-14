#include <stdio.h>

#define LINE_MAX_LEN  80
#define ARR_MAX  255
#define IN_COMM 1
#define OUT_COMM 0


int getlineX(char s[]);
void check(char s[], int len);

int main()
{
    int len;
    char line[ARR_MAX];

    while((len = getlineX(line))> 0) {
        check(line, len);
    }
    return 0;
}


/* getlineX: read a line into s, return length */
int getlineX(char s[])
{
    int c, i;

    for(i = 0; i < ARR_MAX-1 && (c=getchar())!=EOF; ++i)
        s[i] = c;
    if(c == '\n') {
        s[i] = c;
        ++i;
    }
    s[i] = '\0';
    return i;
}

/* check: () , [], {} , "", '', comments, \\ */
void check(char s[], int len)
{
    int i, ns, nl, nw;
    char stack[ARR_MAX], c;

    ns = 0;
    nl = 1;
    nw = 0;
    for (i = 0; i < len; ++i, ++nw) {
        c = s[i];
        if (c == '\n') {
            ++nl;
            nw = 0;
        }
        if (c == '/' && i < len - 1 && s[i+1] == '*') {
            stack[ns++] = 'c';
            ++i;
        } else if (stack[ns-1] == 'c') {
            if (c == '*' && i < len - 1 && s[i+1] == '/') {
                stack[ns--] = '\0';
            } else if(i == len - 1) {
                printf("Err: no /* for */ in line %d:%d\n", nl-1, nw);
                break;
            }
        } else if(c == '{' || c == '(' || c == '[' || c == '\"' || c == '\'')
            stack[ns++] = c;
        else {
            if(c == '}')
                if(stack[ns] != '{') {
                    printf("Err: no { for } in line %d:%d\n", nl, nw);
                    break;
                } else {
                    stack[ns--] = '\0';
                }
            else if(c == ')')
                if(stack[ns] != '(') {
                    printf("Err: no ( for ) in line %d:%d\n", nl, nw);
                    break;
                } else {
                    stack[ns--] = '\0';
                }
            else if(c == ']')
                if(stack[ns] != '[') {
                    printf("Err: no [ for ] in line %d:%d\n", nl, nw);
                    break;
                } else {
                    stack[ns--] = '\0';
                }
            else if(c == '"')
                if(stack[ns] != '\"') {
                    printf("Err: no \" for \" in line %d:%d\n", nl, nw);
                    break;
                } else {
                    stack[ns--] = '\0';
                }
            else if(c == '\'')
                if(stack[ns] != '\'') {
                    printf("Err: no \' for \' in line %d:%d\n", nl, nw);
                    break;
                } else {
                    stack[ns--] = '\0';
                }
            else if(c == '\\' && ((i = len - 1) || s[i+1] == ' ' || s[i+1] == '\t' || s[i+1] == '\n') ) {
                printf("Err: no ele for \\ in line %d:%d\n", nl, nw);
                break;
            }
        }
    }

    if(ns >= 0) {
        for(i = 0; i < ns; ++i)
            if (stack[i] == 'c')
                printf("Err: comments not completed.\n");
            else
                printf("Err: no pairer for %c\n", stack[i]);
    } else
        printf("seems all fine!\n");
}
