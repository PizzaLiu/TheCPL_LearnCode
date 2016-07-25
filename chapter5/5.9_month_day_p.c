#include <stdio.h>

static char daytab[2][13] = {
    {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

/* day_of_year: set day of year from month & day */
int day_of_year(int year, int month, int day)
{
    int i, leap;
    char *p;

    if (month > 12) {
        printf("error: wrong month\n");
        return -1;
    }

    leap = year%4 == 0 && year%100 != 0 && year%400 == 0;
    p = daytab[leap];
    for (i = 1; i < month; ++i)
        day += *++p;
    return day;
}

/* month_day: set month, day from day of year */
void month_day(int year, int yearday, int *pmonth, int *day)
{
    int i, leap;
    char *p;

    leap = year%4 == 0 && year%100 != 0 && year%400 == 0;
    if ((leap == 1 && yearday > 366) || yearday > 365) {
        printf("error: wrong yearday\n");
        return;
    }

    p = daytab[leap];
    for (i = 1; yearday > *p; ++i)
        yearday -= *p++;
    *pmonth = i;
    *day = yearday;
}


int main()
{
    
    int year = 2016;
    int month = 9;
    int day = 10;

    int yearday = day_of_year(year, month, day);

    printf("%d-%d-%d is the %d days of %d.\n", year, month, day, yearday, year);

    month_day(year, ++yearday, &month, &day);

    printf("the %d days of %d is %d-%d-%d\n", yearday, year, year, month, day);
    return 0;
}