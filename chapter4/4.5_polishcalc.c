#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define MAXOP 100
#define NUMBER '0'
#define LIBFUNC '1'

int getop(char []);
void push(double);
double pop(void);
double dofunc(char []);

int main()
{
    int type;
    double op2;
    char s[MAXOP];

    while ((type = getop(s)) != EOF) {
        switch (type) {
            case NUMBER:
                push(atof(s));
                break;
            case LIBFUNC:
                push(dofunc(s));
                break;
            case '+':
                push(pop() + pop());
                break;
            case '*':
                push(pop() * pop());
                break;
            case '-':
                op2 = pop();
                push(pop() - op2);
                break;
            case '/':
                op2 = pop();
                if (op2 != 0.0)
                    push(pop() / op2);
                else
                    printf("error: zero divisor\n");
                break;
            case '%':
                op2 = pop();
                if (op2 != 0.0)
                    push(fmod(pop(), op2));
                else
                    printf("error: zero divisor\n");
                break;
            case '\n':
                printf("\t = %.8g\n", pop());
                break;
            default:
                printf("error: unknown command %s\n", s);
                break;
        }
    }

    return 0;
}

double dofunc(char s[])
{
    double op1, op2;

    if (strcmp(s, "sin") == 0)
        return sin(pop());
    else if (strcmp(s, "cos") == 0)
        return cos(pop());
    else if (strcmp(s, "tan") == 0)
        return tan(pop());
    else if (strcmp(s, "exp") == 0)
        return exp(pop());
    else if (strcmp(s, "pow") == 0) {
        op2 = pop();
        op1 = pop();
        if (op1 == 0 && op2 <= 0)
            printf("error: domain (%g^%g)\n", op1, op2);
        else
            return pow(op1, op2);
    } else {
        printf("error: unknown command %s\n", s);
    }

    return 0.0;
}

//////////////////////////////////////

#define MAXVAL 100

int sp = 0;
double val[MAXVAL];

void push(double f)
{
    if (sp < MAXVAL)
        val[sp++] = f;
    else
        printf("error: stack full, can't push %g\n", f);
}

double pop(void)
{
    if (sp > 0)
        return val[--sp];
    else {
        printf("error: stack empty\n");
        return 0.0;
    }
}

void print_top(void)
{
    if (sp > 0)
        printf("top element of stack: %g\n", val[sp-1]);
    else
        printf("error: stack empty\n");
}

void dumplicate_top(void)
{
    double top;
    if (sp > 0) {
        top = pop();
        push(top);
        push(top);
    } else
        printf("error: stack empty\n");
}

void swap_top(void)
{
    double tmp1, tmp2;
    if (sp > 0) {
        tmp1 = pop();
        tmp2 = pop();
        push(tmp2);
        push(tmp1);
    } else
        printf("error: stack empty\n");
}

void clear(void)
{
    sp = 0;
}

//////////////////////////////////////


#include <ctype.h>

int getch(void);
void ungetch(int);

int getop(char s[])
{
    int i, c;

    while ((s[0] = c = getch()) == ' ' || c == '\t')
        ;
    s[1] = '\0';
    i = 0;
    if (isalpha(c)) {
        while(isalpha(s[++i] = c = getch()))
            ;
        s[i] = '\0';
        if (c != EOF)
            ungetch(c);
        return LIBFUNC;
    }
    if (!isdigit(c) && c != '.')
        return c;
    if (isdigit(c))
        while (isdigit(s[++i] = c = getch()))
            ;
    s[i] = '\0';
    if (c != EOF)
        ungetch(c);
    return NUMBER;
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
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}

