#include <stdio.h>

/* count lines in input */
main()
{
    int c, nsp, ntab, nl;

    nsp = 0;
    ntab = 0;
    nl = 0;
    while((c = getchar()) != EOF)
        if(c == ' ')
            ++nsp;
        else if(c == '\t')
            ++ntab;
        else if(c == '\n')
            ++nl;
    printf("Space:%d, Tab:%d, Line:%d", nsp, ntab, nl);

}