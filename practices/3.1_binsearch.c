#include <stdio.h>

int binsearch(int x, int v[], int n);

int main()
{
    int x = 5;
    int n = 10, i;
    int v[n];

    for(i = 0; i < n; ++i)
        v[i] = i;

    printf("binsearch(%d, [0, 1, 2 .... 9], %d) = %d\n", x, n, binsearch(x, v, n));
    return 0;
}


int binsearch(int x, int v[], int n)
{
    int low, high, mid;

    low = 0;
    high = n - 1;

    while(high > low) {
        mid = (low+high) / 2;
        if(x > v[mid])
            low = mid + 1;
        else
            high = mid;
    }

    return x == v[low] ? low : -1;
}