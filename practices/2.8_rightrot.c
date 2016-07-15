#include <stdio.h>

unsigned int rightrot(unsigned int x, unsigned int n);


int main()
{
    int x = 1025;
    unsigned int n = 2;

    printf("rightrot(%u, %u) = %u\n", x, n, rightrot(x, n));

    return 0;
}

unsigned int rightrot(unsigned int x, unsigned int n)
{
    while(n > 0) {
        if(x & 1)
            x = (x >> 1) | ~(~0u >> 1);
        else
            x = (x >> 1);
        --n;
    }
    return x;
}
