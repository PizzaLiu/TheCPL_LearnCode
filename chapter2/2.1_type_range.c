#include <stdio.h>
#include <limits.h>
#include <math.h>

unsigned long long pow2(int base, int n);

int main()
{
    printf("----- In <limits.h> ----------\n");
    printf("signed char: %d ~ %d\n", CHAR_MIN, CHAR_MAX);
    printf("unsigned char: %d ~ %d\n", 0, UCHAR_MAX);
    printf("signed short: %d ~ %d\n", SHRT_MIN, SHRT_MAX);
    printf("unsigned short: %d ~ %d\n", 0, USHRT_MAX);
    printf("signed int: %d ~ %d\n", INT_MIN, INT_MAX);
    printf("unsigned int: %d ~ %u\n", 0, UINT_MAX);
    printf("signed long: %ld ~ %ld\n", LONG_MIN, LONG_MAX);
    printf("unsigned long: %d ~ %lu\n", 0, ULONG_MAX);
    printf("signed long long: %lld ~ %llu\n", LLONG_MIN, LLONG_MAX);
    printf("unsigned long long: %d ~ %llu\n", 0, ULLONG_MAX);


    char c;
    unsigned char uc;
    short s;
    unsigned short us;
    int i;
    unsigned int ui;
    long l;
    unsigned long ul;
    long long ll;
    unsigned long long ull;


    int char_min, char_max, uchar_min, uchar_max;
    int short_min, short_max, ushort_min, ushort_max;
    long int_min, int_max, uint_min, uint_max;
    long long long_min, long_max, ulong_min, ulong_max;
    long long llong_min, llong_max, ullong_min, ullong_max;

    char_min = (int)(-1 * pow(2, 8*sizeof(c)) / 2);
    char_max = (int)(pow(2, 8*sizeof(c)) / 2 - 1);
    uchar_min = 0;
    uchar_max = (int)(pow(2, 8*sizeof(uc)) - 1);

    short_min = (int)(-1 * pow(2, 8*sizeof(s)) / 2);
    short_max = (int)(pow(2, 8*sizeof(s)) / 2 - 1);
    ushort_min = 0;
    ushort_max = (int)(pow(2, 8*sizeof(us)) - 1);

    int_min = (long)(-1 * pow(2, 8*sizeof(i)) / 2);
    int_max = (long)(pow(2, 8*sizeof(i))/2 - 1);  //
    uint_min = 0;
    uint_max = (long)(pow(2, 8*sizeof(ui)) - 1);

    long_min = (long long)(-1 * pow2(2, 8*sizeof(l)-1));
    long_max = (long long)(pow2(2, 8*sizeof(l)-1) - 1);
    ulong_min = 0;
    ulong_max = (long long)(pow2(2, 8*sizeof(ul)) - 1);

    llong_min = (long long)(-1 * pow2(2, 8*sizeof(ll)-1));
    llong_max = (long long)(pow2(2, 8*sizeof(ll)-1) - 1);
    ullong_min = 0;
    ullong_max = (unsigned long long)(pow2(2, 8*sizeof(ull)) - 1);

    printf("----- Directly Compute ----------\n");
    printf("signed char: %d ~ %d\n", char_min, char_max);
    printf("unsigned char: %d ~ %d\n", uchar_min, uchar_max);
    printf("signed short: %d ~ %d\n", short_min, short_max);
    printf("unsigned short: %d ~ %d\n", ushort_min, ushort_max);
    printf("signed int: %ld ~ %ld\n", int_min, int_max);
    printf("unsigned int: %ld ~ %ld\n", uint_min, uint_max);
    printf("signed long: %lld ~ %llu\n", long_min, long_max);
    printf("unsigned long: %lld ~ %llu\n", ulong_min, ulong_max);
    printf("signed long long: %lld ~ %llu\n", llong_min, llong_max);
    printf("unsigned long long: %lld ~ %llu\n", ullong_min, ullong_max);

    return 0;
}

unsigned long long pow2(int base, int n)
{
    unsigned long long r;

    for(r = 1; n > 0; --n)
        r *= base;

    return r;
}
