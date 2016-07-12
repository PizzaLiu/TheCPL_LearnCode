#include <stdio.h>

/* print input to single word in a line */
main()
{
    int c;

    while((c = getchar()) != EOF) {
        if(c == ' ' || c == '\t')
            printf("\n");
        else
            putchar(c);
    }
}