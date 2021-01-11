/**
 * Exercise 4-9 - K&R 2nd ED
 * =========================
 * > by ANK-dev
 *
 * 'getch' and 'ungetch' EOF support
 * ---------------------------------
 */

#include <stdio.h>
#include <string.h>

#define BUFSIZE 100

int getch(void);
void ungetch(int c);
void ungets(const char s[]);

/*
 * EOF is defined as -1. 'char' can't be a negative value, so, by changing the
 * buffer type to 'int', 'getch' and 'ungetch' can handle EOFs without a problem
 */
int buf[BUFSIZE];
int  bufp = 0;

int main()
{
	int c;
	const char s1[] = "this string will be followed by an EOF";
	const char s2[] = "this string will NOT be shown due to the previous EOF";

	ungets(s2);
	ungetch(EOF);
	ungets(s1);

	/* only a single char will pushed to stdout */
	while((c = getch()) != EOF)
		putchar(c);

	return 0;
}

int getch(void)
{
	return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c)
{
	if (bufp >= BUFSIZE)
		printf("ungetch: too many characters\n");
	else
		buf[bufp++] = c;
}

/* ungets:  pushes string into buffer in reverse order */
void ungets(const char s[])
{
	unsigned int i = strlen(s);

	while (i > 0)
		ungetch(s[--i]);
}