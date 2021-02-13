#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "headers/getword.h"

#define BUFSIZE 100

static char buf[BUFSIZE];          /* buffer for ungetch           */
static int  bufp = 0;              /* next free position in buf    */

/* getword:  get next word or character from input */
int getword(char *word, int lim)
{
	int c, d;
	char *w = word;

	while (isspace(c = getch()) && c != '\n')
		;
	if (c != EOF)
		*w++ = c;
	if (isalpha(c) || c == '_' || c == '#') {
		for (; --lim > 0; w++)
			if (!isalnum(*w = getch()) && *w != '_') {
				ungetch(*w);
				break;
			}
	} else if (c == '\'' || c == '"') {
		for (; --lim > 0; w++)
			if ((*w = getch()) == '\\')
				*++w = getch();
			else if (*w == c) {
				w++;
				break;
			} else if (*w == EOF)
				break;

	} else if (c == '/') {
		if ((d = getch()) == '*')
			c = comment();
		else
			ungetch(d);
	}
	*w = '\0';
	return c;
}


/* getch:  get a (possibly pushed back) character */
int getch(void)
{
	return (bufp > 0) ? buf[--bufp] : getchar();
}

/* ungetch:  push character back on input */
void ungetch(int c)
{
	if (bufp >= BUFSIZE)
		printf("ungetch: too many characters\n");
	else
		buf[bufp++] = c;
}

/* comment:  skip over comment and return a character */
int comment(void)
{
	int c;
	while ((c = getch()) != EOF)
		if (c == '*') {
			if ((c = getch()) == '/')
				break;
			else
				ungetch(c);
		}
	return c;
}

/* strdup: make a duplicate of s */
char *strdup(char *s)
{
	char *p;

	p = (char *) malloc(strlen(s)+1);   /* +1 for '\0' */
	if (p != NULL)
		strcpy(p, s);
	return p;
}

/* skipblanks: skip blank and tab characters */
void skipblanks(void)
{
	int c;

	while ((c = getch()) == ' ' || c == '\t')
		;
	ungetch(c);
}

/* error: print error message and skip the rest of the line */
void error(int c, const char *s)
{
	printf("error: %s\n", s);
	while (c != EOF && c != '\n')
		c = getch();
}