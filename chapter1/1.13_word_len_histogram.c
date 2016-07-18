#include <stdio.h>

#define MAX_WORD 255

main()
{
    int c, i, j, n, max;
    int nw[MAX_WORD];

    max = n = 0;
    for (i = 0; i < MAX_WORD; ++i)
        nw[i] = 0;

    i = 0;
    while((c = getchar()) != EOF) {
        if(c == ' ' || c == '\n' || c == '\t') {
            if(n > max) max = n;
            nw[i] = n;
            ++i;
            n = 0;
        } else {
            ++n;
        }
    }

    for (i = 0; i < MAX_WORD && nw[i] > 0; ++i)
            printf("--");
    printf("----\n");

    for(j = max; j > 0; --j) {
        printf("| %d ", j);
        for (i = 0; i < MAX_WORD && nw[i] > 0; ++i)
            if(nw[i] >= j) printf("* ");
            else printf("  ");
        printf(" |\n");
    }

    printf("| / ");
    for (i = 0; i < MAX_WORD && nw[i] > 0;)
            printf("%d ", ++i);

    printf(" |\n");
    for (i = 0; i < MAX_WORD && nw[i] > 0; ++i)
            printf("--");
    printf("----\n");

}