/*
 * Exercise 5-04 - K&R 2nd ED
 * -- ANK-dev
 *
 * strend: checks if the string 't' occurs at the end of the string 's'
 */

#include <stdio.h>

#define ARRLENGTH 20

int strend(char *s, char *t);

int main()
{
	char arr0[] = "Hello World";
	char arr1[] = "World";

	printf("%d\n", strend(arr0, arr1));
	return 0;
}

int strend(char *s, char *t)
{
	/* search for the beginning of 't' in 's' before its end */
	while (*s != *t && *s)
		s++;
	/* match characters until the end of either string */
	while (*s == *t && (*s && *t)) { 
		s++; t++;
	}
	/* if both end in '\0', 't' is at the end of 's' */
	if (!*s && !*t)
		return 1;
	else
		return 0;
}