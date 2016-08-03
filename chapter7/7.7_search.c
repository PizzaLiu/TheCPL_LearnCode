#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXLINE 200

void search(char *fname, char *pattern)
{
    FILE *fp;
    char line[MAXLINE];

    if (fname == NULL)
        fp = stdin;
    else {
        fp = fopen(fname, "r");
        if (fp == NULL) {
            printf("error: can not open %s\n", fname);
            return;
        }
    }

    while (fgets(line, MAXLINE, fp) != NULL)
        if (strstr(line, pattern)) {
            if (fname == NULL)
                printf("%s\n", line);
            else
                printf("%s: %s\n", fname, line);
        }
    fclose(fp);
}


int main(int argc, char *argv[])
{
    int i;

    if (argc < 2) {
        printf("please input a search pattern\n");
        exit(1);
    }

    if (argc == 2)
        search(NULL, argv[1]);
    else
        for (i = 2; i < argc; ++i)
            search(argv[i], argv[1]);
    return 0;
}