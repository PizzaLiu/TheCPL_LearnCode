#include <stdio.h>

#define swap(t, x, y) t tmp; tmp = x; x = y; y = tmp;

int main()
{
    float x = 10;
    float y = 11;
    printf("x=%g,y=%g\n", x, y);
    printf("swap(x, y)...\n");
    swap(float, x, y);
    printf("x=%g,y=%g\n", x, y);
    return 0;
}