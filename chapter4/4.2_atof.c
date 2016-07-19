#include <stdio.h>
#include <ctype.h>

double atof(char s[]);

double atof(char s[])
{
    double val, power;
    int i, sign, esign, exp;

    for (i = 0; isspace(s[i]); i++)
        ;
    sign = (s[i] == '-') ? -1 : 1;
    if (s[i] == '+' || s[i] == '-')
        i++;
    for (val = 0.0; isdigit(s[i]); i++)
        val = 10.0 * val + (s[i] - '0');
    if (s[i] == '.')
        i++;
    for (power = 1.0; isdigit(s[i]); i++) {
        val = 10.0 * val + (s[i] - '0');
        power *= 10;
    }

    if (s[i] == 'e' || s[i] == 'E')
        i++;
    esign = (s[i] == '-') ? -1 : 1;
    if (s[i] == '+' || s[i] == '-')
        i++;
    for (exp = 0.0; isdigit(s[i]); i++)
        exp = 10.0 * exp + (s[i] - '0');

    do {
        if(esign < 0)
            power *= 10.0;
        else
            power /= 10.0;
    } while(--exp);

    return sign * val / power;
}


int main()
{
    char s[] = "123.45e-6";

    printf("atof(\"%s\") = %.8f\n", s, atof(s));
    return 0;
}