#include <stdio.h>

int bitcount(unsigned x);

int main()
{
    unsigned x = 1024;

    printf("bitcount(%u) = %d\n", x, bitcount(x));
    return 0;
}



int bitcount(unsigned x)
{
    int b;

    for(b = 0; x > 0; x &= (x-1))
        ++b;
    return b;
}