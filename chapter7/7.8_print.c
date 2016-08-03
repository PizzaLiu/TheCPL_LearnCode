#include <stdio.h>

#define MAXLINE 1000


int main(int argc, char *argv[])
{
    int status = 0, page = 0;
    FILE *fp;
    char line[MAXLINE];

    while (*++argv) {
        fp = fopen(*argv, "r");

        if (fp == NULL) {
            status = 1;
            fprintf(stderr, "can not open %s\n", *argv);
            continue;
        }

        printf("Page: %d File: %s\n", ++page, *argv);
        while (fgets(line, MAXLINE, fp))
            printf("%s\n", line);

        fclose(fp);
    }

    return status;
}

