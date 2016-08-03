#include <stdio.h>
#include <stdlib.h>

#define MAXLINE 100

int main(int argc, char *argv[])
{
    int line_compare(char *line1, char *line2);
    FILE *fp1, *fp2;
    char line1[MAXLINE], line2[MAXLINE];

    if (argc != 3) {
        fprintf(stderr, "error: no enough argv\n");
        exit(1);
    }
    if ((fp1 = fopen(argv[1], "r")) == NULL) {
        fprintf(stderr, "error: can not open %s\n", argv[1]);
        exit(1);
    }
    if ((fp2 = fopen(argv[2], "r")) == NULL) {
        fprintf(stderr, "error: can not open %s\n", argv[2]);
        exit(1);
    }

    fprintf(stdout, "start to compare %s and %s\n", argv[1], argv[2]);

    while(fgets(line1, MAXLINE, fp1) != NULL) {
        ;
        if (fgets(line2, MAXLINE, fp2) == NULL) {
            fprintf(stdout, " file1:%s file2:%s\n", line1, line2);
            break;
        } else if (line_compare(line1, line2) != 0) {
            fprintf(stdout, " file1:%s file2:%s\n", line1, line2);
            break;
        }
    }

    if (fgets(line1, MAXLINE, fp1) == NULL && fgets(line2, MAXLINE, fp2) != NULL)
        fprintf(stdout, " file1:%s file2:%s\n", line1, line2);

    fclose(fp1);
    fclose(fp2);

    exit(0);
}


int line_compare(char *line1, char *line2)
{
    int i;

    for (i = 0; line1[i] != '\0'; ++i)
        if (line2[i] == '\0' || line1[i] - line2[i] > 0)
            return 1;
        else if (line1[i] - line2[i] < 0)
            return -1;

    if (line2[i] != '\0')
        return -1;
    else
        return 0;
}