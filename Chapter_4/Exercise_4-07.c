/**
 * Exercise 4-7 - K&R 2nd ED
 * =========================
 * > by ANK-dev
 *
 * 'ungets(s)'
 * -----------
 */

#include <stdio.h>
#include <string.h>

#define BUFSIZE 100

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

	/* reads string char by char and outputs to stdout */
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