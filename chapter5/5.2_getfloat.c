#include <stdio.h>
#include <ctype.h>

int getch(void);
void ungetch(int);

int getfloat(float *pn)
{
    int c, sign, pow = -1;

    while (isspace(c = getch()))
        ;
    if (!isdigit(c) && c != EOF && c != '+' && c != '-' && c != '.') {
        ungetch(c);
        return 0;
    }
    sign = (c == '-') ? -1 : 1;
    if (c== '+' || c == '-') {
        c = getch();
        if (!isdigit(c)) {
            ungetch(sign > 0 ? '+' : '-');
            return 0;
        }
    }

    for (*pn = 0.0; isdigit(c) || c == '.'; c = getch()) {
        if (c == '.') {
            if (pow == -1)
                pow = 0;
            else {
                printf("error: tow dots.\n");
                return 0;
            }
        }
        if (c != '.') *pn = 10 * *pn + (c - '0');
        if (pow >= 0 && c != '.')
            ++pow;
    }
    while(pow-- > 0)
        *pn /= 10;

    *pn *= sign;
    if (c != EOF)
        ungetch(c);
    return c;
}


#define SIZE 255

int main()
{
    int n, i;
    float array[SIZE];

    for (n = 0; n < SIZE && getfloat(&array[n]) != EOF; n++)
        ;

    for (i = 0; i < n; i++)
        printf("%f ", array[i]);

    printf("\n");
    return 0;
}

//////////////////////////////////////

#define BUFSIZE 100

char buf[BUFSIZE];
int bufp = 0;

int getch(void)
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c)
{
    if (c == EOF)
        printf("ungetch: can't ungetch EOF\n");
    else if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}