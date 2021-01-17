/**
 * Exercise 4-11 - K&R 2nd ED
 * ==========================
 * > by ANK-dev
 *
 * getop w/o ungetch (using static variable)
 * -----------------------------------------
 */

#include <stdio.h>
#include <ctype.h>

#define NUMBER '0'

int getch(void);
void ungetch(int);

/* getop:  get next operator or numeric operand */
int getop(char s[])
{
	int i, c;

	/* remembers last char pushed onto input */
	static int lastc = 0;

	/*
	 * if previous char doesn't exist, gets next char; else pushes previous char
	 * onto input
	 */
	if (lastc == 0)
		c = getch();
	else {
		c = lastc;
		lastc = 0;
	}

	/* examines the current char, then gets the next one */
	while ((s[0] = c) == ' ' || c == '\t')
		c = getch();
	s[1] = '\0';
	if (!isdigit(c) && c != '.')
		return c;     /* not a number */
	i = 0;
	if (isdigit(c))   /* collect integer part */
		while (isdigit(s[++i] = c = getch()))
			;
	if (c == '.')     /* collect fraction part */
		while (isdigit(s[++i] = c = getch()))
			;
	s[i] = '\0';
	if (c != EOF)
		lastc = c;
	return NUMBER;
}