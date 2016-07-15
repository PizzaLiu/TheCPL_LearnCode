#include <stdio.h>

int setbits(int x, unsigned int p, unsigned int n, int y);

int main()
{
    int x, y;
    unsigned int p, n;

    x = 1025;
    p = 2;
    n = 3;
    y = 2;

    printf("setbits(%d, %u, %u, %d) = %d\n", x, p, n, y, setbits(x, p, n, y));

    return 0;
}

int setbits(int x, unsigned int p, unsigned int n, int y)
{
    int i = x & ~(~0 << n) << (p+1-n);
    int j = (y & ~(~0 << n)) << (p+1-n);

    return x - i + j;
}