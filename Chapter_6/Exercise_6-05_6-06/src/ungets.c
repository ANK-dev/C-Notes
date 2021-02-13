#include <stdio.h>
#include <string.h>

#define BUFSIZE 100

static char buf[BUFSIZE];
static int  bufp = 0;

static void ungetch(int c)
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