#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAXSTRINGLEN "10"

int main(int argc, char *argv[])
{
    char *s;

    if (argc != 2) return 1;
    printf("%." MAXSTRINGLEN "s", argv[1]);
    return 0;
}