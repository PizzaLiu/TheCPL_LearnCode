#include <stdio.h>

int invert(int x, unsigned int p, unsigned int n);

int main()
{
    int x;
    unsigned int p, n;

    x = 1025;
    p = 2;
    n = 3;

    printf("invert(%d, %u, %u) = %d\n", x, p, n, invert(x, p, n));

    return 0;
}


int invert(int x, unsigned int p, unsigned int n)
{
    int mask = (~(~0 << n) << (p+1-n));
    int i = x & mask;
    return x - i + (~i & mask);
}