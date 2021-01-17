/**
 * Exercise 4-13 - K&R 2nd ED
 * ==========================
 * > by ANK-dev
 *
 * reverse (recursive version)
 * ---------------------------
 */

#include <string.h>

void reverse(char s[]);
void reverser(char s[], int i, int len);

/* reverse:  reverse string s in place */
void reverse(char s[])
{
	/* keep the same interface to reverse,
	   reverser does the calculations instead */
	reverser(s, 0, strlen(s));
}

void reverser(char s[], int i, int len)
{
	int c, j;

	j = len - (i + 1);
	/* swap characters from outside-in */
	if (i < j) {
		c = s[i];
		s[i] = s[j];
		s[j] = c;
		reverser(s, ++i, len);
	}
}