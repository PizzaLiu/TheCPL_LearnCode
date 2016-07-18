#include <stdio.h>

/* print Celsius-Fahrenheit table
    for fahr = 0, 5, ..., 100; floating-point version */

main() {
    float fahr, celsius;
    float lower, upper, step;

    lower = 0;
    upper = 100;
    step = 5;

    printf("[Celsius] [Fahrenheit]\n");

    celsius = lower;
    while(celsius <= upper) {
        fahr = (5.0/9.0) * celsius + 32.0;
        printf("%6.0f %11.1f\n", celsius, fahr);
        celsius = celsius + step;
    }
}

