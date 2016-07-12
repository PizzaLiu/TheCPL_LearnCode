#include <stdio.h>

main()
{
    int c, prec;

    while((c = getchar()) != EOF) {
        if(c != ' ' || (c == ' ' && prec != ' ')) putchar(c);
        prec = c;
    }
}