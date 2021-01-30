/*
 * Exercise 5-03 - K&R 2nd ED
 * -- ANK-dev
 *
 * strcat (pointer version)
 */

#include <stdio.h>

#define ARRLENGTH 20

void strcat(char *s, char *t);

int main()
{
	char arr0[ARRLENGTH] = "Hello";
	char arr1[] = " World";

	strcat(arr0, arr1);
	printf("%s\n", arr0);
	return 0;
}

void strcat(char *s, char *t)
{
	while (*s)    /* find end of s */
		s++;
	while ((*s++ = *t++))    /* copy t */
		;
}