/**
 * Exercise 4-8 - K&R 2nd ED
 * =========================
 * > by ANK-dev
 *
 * 'ungets(s) - single character limit'
 * ------------------------------------
 */

#include <stdio.h>
#include <string.h>

#define BUFSIZE 1

int getch(void);
void ungetch(int c);
void ungets(const char s[]);

char buf[BUFSIZE];
int  bufp = 0;

int main()
{
	int c;
	const char s[] = "this is the string I want to push back";
	ungets(s);

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
		/* avoid error spam, ignore any character beyond the first */
		;
	else
		buf[bufp++] = c;
}

/* ungets:  pushes string into stdin in reverse order */
void ungets(const char s[])
{
	unsigned int i = strlen(s);

	while (i > 0)
		ungetch(s[--i]);
}