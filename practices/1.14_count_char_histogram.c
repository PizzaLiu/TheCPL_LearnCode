#include <stdio.h>

#define CHAR_LEN 26
#define LOW_OFFSET 96
#define UPPER_OFFSET 64

// a: 97, A: 65
main()
{
    int c, i, j, max;
    int low[CHAR_LEN], upper[CHAR_LEN];

    max = 0;

    for(i = 0; i < CHAR_LEN; ++i) {
        low[i] = 0;
        upper[i] = 0;
    }

    while((c = getchar()) != EOF) {
        if(c > LOW_OFFSET && c <= LOW_OFFSET + CHAR_LEN)
            ++low[c-'a'];
        else if(c > UPPER_OFFSET && c <= UPPER_OFFSET + CHAR_LEN)
            ++upper[c-'A'];
    }


    for (i = 0; i <= CHAR_LEN; ++i)
            printf("--");
    printf("----\n");

    for(i = 0; i < CHAR_LEN; ++i) {
        if(low[i] > max) max = low[i];
    }

    for(j = max; j > 0; --j) {
        printf("| %d ", j);
        for (i = 0; i < CHAR_LEN; ++i)
            if(low[i] >= j) printf("* ");
            else printf("  ");
        printf(" |\n");
    }

    printf("| / ");
    for (i = 1; i <= CHAR_LEN; ++i)
            printf("%c ", LOW_OFFSET+i);

    printf(" |\n");
    for (i = 0; i <= CHAR_LEN; ++i)
            printf("--");
    printf("----\n");

    //////////////////////////
    max = 0;
    for(i = 0; i < CHAR_LEN; ++i) {
        if(upper[i] > max) max = upper[i];
    }

    for(j = max; j > 0; --j) {
        printf("| %d ", j);
        for (i = 0; i < CHAR_LEN; ++i)
            if(upper[i] >= j) printf("* ");
            else printf("  ");
        printf(" |\n");
    }

    printf("| / ");
    for (i = 1; i <= CHAR_LEN; ++i)
            printf("%c ", UPPER_OFFSET+i);

    printf(" |\n");
    for (i = 0; i <= CHAR_LEN; ++i)
            printf("--");
    printf("----\n");

}