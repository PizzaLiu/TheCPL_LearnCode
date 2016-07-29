#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

/* minscanf: minimal scanf with variable argument list */
void minscanf(char *fmt, ...)
{
    va_list ap; /* points to each unnamed arg in turn */
    char *p, *sval, *cp;
    int *ip;
    double *dp;

    va_start(ap, fmt); /* make ap point to 1st unnamed arg */
    for (p = fmt; *p; p++) {
        if (*p != '%') {
            putchar(*p);
            continue;
        }
        switch (*++p) {
            case 'd':
                ip = va_arg(ap, int *);
                scanf("%d", ip);
                break;
            case 'f':
                dp = va_arg(ap, double *);
                scanf("%lf", dp);
                break;
            case 's':
                for (sval = va_arg(ap, char *); *sval; sval++)
                    putchar(*sval);
                break;
            case 'c':
                cp = va_arg(ap, char *);
                scanf("%c", cp);
                break;
            default:
                putchar(*p);
                break;
        }
    }
    va_end(ap); /* clean up when done */
}

int main()
{
    char c;
    int i;
    minscanf("char c = %c", &c);
    minscanf("int i = %d", &i);
    printf("c: %c, i: %d\n", c, i);
    return 0;
}