/*
 * Exercise 5-05 - K&R 2nd ED
 * -- ANK-dev
 *
 * strncpy, strncat, strncmp: operate on the first 'n' characters
 */

#include <stdio.h>

char *strncpy(char *s, const char *t, int n);
char *strncat(char *s, const char *t, int n);
int strncmp(const char *s, const char *t, int n);

int main()
{
	char arr[20];

	printf("%s\n", strncpy(arr, "Hello World", 6));

	printf("%s\n", strncat(arr, "Planet Earth", 6));

	printf("%d\n", strncmp(arr, "Hello", 5));
	return 0;
}

char *strncpy(char *s, const char *t, int n)
{
	char *s_start = s;

	while (*t && n-- > 0)    /* copy t into s */
		*s++ = *t++;
	while (n-- > 0)
		*s++ = '\0';         /* pad with '\0's if n is larger than t */

	return s_start;
}


char *strncat(char *s, const char *t, int n)
{
	char *s_start = s;

	for (; *s; s++)               /* find the end of s */
		;
	while (*t && n-- > 0)    /* copy t into s*/
		*s++ = *t++;
	*s = '\0';

	return s_start;
}

int strncmp(const char *s, const char *t, int n)
{
	/* compare characters until n == 0 or '\0' is found */
	while ((*s == *t) && *s != '\0' && --n > 0) {
		s++; t++;
	}

    /* return the lexographical diference between the characters */
	return *s - *t;
}