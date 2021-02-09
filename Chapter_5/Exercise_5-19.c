/*
 * Exercise 5-19 - K&R 2nd ED
 * -- ANK-dev
 *
 * undcl:  convert word description to declaration (remove redundant
 * parentheses)
 *
 * Convert descriptions to the following format before input:
 *
 * "x is a pointer to char" --> "x * char"
 * "daytab is a pointer to an array of [13] int" --> "daytab * [13] int"
 * "daytab is an array of [13] pointers to int" --> "daytab [13] * int"
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXTOKEN 100

#define BUFSIZE  100

enum {NAME, PARENS, BRACKETS};
enum {NO, YES};

void dcl(void);
void dirdcl(void);

int gettoken(void);
int nexttoken(void);
void errmsg(const char *);

int  getch(void);
void ungetch(int c);
void bufclr(void);

int  tokentype;             /* type of last token           */
int  prevtoken;             /* prev token is available      */
char token[MAXTOKEN];       /* last token string            */
char name[MAXTOKEN];        /* identifier name              */
char datatype[MAXTOKEN];    /* data type = char, int, etc.  */
char out[1000];             /* output string                */

char buf[BUFSIZE];          /* buffer for ungetch           */
int  bufp = 0;              /* next free position in buf    */

/* convert declaration to words */
int main()
{
	int type;
	char temp[1000 + MAXTOKEN];

	while (gettoken() != EOF) {
		strcpy(out, token);
		while ((type = gettoken()) != '\n')
			if (type == PARENS || type == BRACKETS)
				strcat(out, token);
			else if (type == '*') {
				if ((type = nexttoken()) == PARENS || type == BRACKETS)
					sprintf(temp, "(*%s)", out);
				else
					sprintf(temp, "*%s", out);
				strcpy(out, temp);
			} else if (type == NAME) {
				sprintf(temp, "%s %s", token, out);
				strcpy(out, temp);
			} else
				printf("invalid input at %s\n", token);
		printf("%s\n", out);
	}
	return 0;
}

/* dcl:  parse a declarator */
void dcl(void)
{
	int ns;

	for (ns = 0; gettoken() == '*'; )   /* count *'s */
		ns++;
	dirdcl();
	while (ns-- > 0)
		strcat(out, " pointer to");
}

/* dirdcl:  parse a direct declarator */
void dirdcl(void)
{
	int type;

	if (tokentype == '(') {             /* ( dcl ) */
		dcl();
		if (tokentype != ')') {
			errmsg("error: missing )\n");
		}
	} else if (tokentype == NAME)       /* variable name */
		strcpy(name, token);
	else {
		errmsg("error: expected name or (dcl)\n");
	}
	while ((type = gettoken()) == PARENS || type == BRACKETS)
		if (type == PARENS)
			strcat(out, " function returning");
		else {
			strcat(out, " array");
			strcat(out, token);
			strcat(out, " of");
		}
}

/* gettoken:  return next token */
int gettoken(void)
{
	int c, getch(void);
	void ungetch(int);
	char *p = token;

	if (prevtoken == YES) {
		prevtoken = NO;
		return tokentype;
	}

	while ((c = getch()) == ' ' || c == '\t')
		;
	if (c == '(') {
		if ((c = getch()) == ')') {
			strcpy(token, "()");
			return tokentype = PARENS;
		} else {
			ungetch(c);
			return tokentype = '(';
		}
	} else if (c == '[') {
		for (*p++ = c; (*p++ = getch()) != ']'; )
			;
		*p = '\0';
		return tokentype = BRACKETS;
	} else if (isalpha(c)) {
		for (*p++ = c; isalnum(c = getch()); )
			*p++ = c;
		*p = '\0';
		ungetch(c);
		return tokentype = NAME;
	} else
		return tokentype = c;
}

/* nexttoken:  get the next token and push it back */
int nexttoken(void)
{
	int type;

	type = gettoken();
	prevtoken = YES;
	return type;
}

/* getch:  get a (possibly pushed back) character */
int getch(void)
{
	return (bufp > 0) ? buf[--bufp] : getchar();
}

/* ungetch  push character back on input */
void ungetch(int c)
{
	if (bufp >= BUFSIZE)
		printf("ungetch: too many characters\n");
	else
		buf[bufp++] = c;
}

void errmsg(const char *msg)
{
	printf("%s", msg);
	prevtoken = YES;
}