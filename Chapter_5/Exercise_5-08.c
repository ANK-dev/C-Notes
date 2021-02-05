/*
 * Exercise 5-08 - K&R 2nd ED
 * -- ANK-dev
 *
 * day of year, month & day:  date conversion
 */

#include <stdio.h>

int day_of_year(int year, int month, int day);
void month_day(int year, int yearday, int *pmonth, int *pday);

static char daytab[2][13] = {
	{0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
	{0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
};

int main()
{
	int y = 2021, m = 2, d = 3, yd = 365;

	printf("Day of the year for year=%d, month=%d, day=%d: %d\n",
	       y, m, d, day_of_year(y, m, d));
	month_day(y, yd, &m, &d);
	printf("Month & day for year=%d, yearday=%d: month=%d, day=%d\n",
	       y, yd, m, d);
	return 0;
}

/* day_of_year:  set day of year from month & day */
int day_of_year(int year, int month, int day)
{
	int i, leap;

	/* error checking */
	if (year < 0)
		return -1;
	if (month < 1 || month > 12)
		return -1;

	leap = (year%4 == 0 && year%100 != 0) || year%400 == 0;

	/* error checking */
	if (day < 1 || day > daytab[leap][month])
		return -1;

	for (i = 1; i < month; i++)
		day += daytab[leap][i];
	return day;
}

/* month_day:  set month, day from day of year */
void month_day(int year, int yearday, int *pmonth, int *pday)
{
	int i, leap;

	/* error checking */
	if (year < 1) {
		*pmonth = -1;
		*pday = -1;
		return;
	}

	leap = (year%4 == 0 && year%100 != 0) || year%400 == 0;

	/* error checking */
	if (   (yearday < 1)
	    || (yearday > 365 && leap == 0)
	    || (yearday > 366 && leap == 1))
	{
		*pmonth = -1;
		*pday = -1;
		return;
	}

	for (i = 1; yearday > daytab[leap][i]; i++)
		yearday -= daytab[leap][i];
	*pmonth = i;
	*pday = yearday;
}