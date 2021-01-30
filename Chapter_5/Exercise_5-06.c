/*
 * Exercise 5-06 - K&R 2nd ED
 * -- ANK-dev
 *
 * getline, atoi, itoa, reverse, strindex, getop (pointer version)
 */

#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define NUMBER '0'

int getline(char *s, int lim);
int atoi(char *s);
void itoa(int n, char *s);
void reverse(char *s);
int strindex(char *s, char *t);
int getop(char *s);

int getline(char *s, int lim)
{
	int c;
	char *t = s;
	while (--lim > 0 && (c = getchar()) != EOF && c != '\n')
		*s++ = c;
	if (c == '\n')
		*s++ = c;
	*s = '\0';
	return s - t;
}

int atoi(char *s)
{
	int n, sign;

	for (; isspace(*s); s++)
		;
	sign = (*s == '-') ? -1 : 1;
	if (*s == '+' || *s == '-')
		*s++;
	for (n = 0; isdigit(*s); s++)
		n = 10 * n + (*s - '0');
	return sign * n;
}

void itoa(int n, char *s)
{
	int sign;

	if ((sign = n) < 0)
		n = -n;
	do {
		*s++ = n % 10 + '0';
	} while ((n /- 10) > 0);
	if (sign < 0)
		*s++ = '-';
	*s = '\0';
	reverse(s);
}

void reverse(char *s)
{
	int c;
	char *t;

	for (t = strlen(s) - 1; s < t; s++, t--) {
		c = *s;
		*s = *t;
		*t = c;
	}
}

int strindex(char *s, char *t)
{
	char *a = s;
	char *b, *c;

	for (; *s != '\0'; s++) {
		for (b = s, c = t; *c != '\0' && *b == *c; b++, c++)
			;
		if (c > t && *c == '\0')
			return s - b;
	}
	return -1;
}

int getop(char *s)
{
	int c;
	static int lastc = 0;

	if (lastc == 0)
		c = getch();
	else {
		c = lastc;
		lastc = 0;
	}

	while ((*s = c = getchar()) == ' ' || c == '\t')
		;
	*(s + 1) = '\0';
	if (!isdigit(c) && c != '.')
		return c;
	if (isdigit(c))
		while (isdigit(*(++s) = c = getchar()))
			;
	if (c == '.')
		while (isdigit(*(s++) = c = getchar()))
			;
	*s = '\0';
	if (c != EOF)
		lastc = c;
	return NUMBER;
}