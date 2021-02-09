
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "headers/dcl.h"

extern char datatype[];
extern char token[];
extern char datatype[];
extern int  tokentype;
extern char out[];
extern char name[];
extern int prevtoken;

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
	} else if (tokentype == NAME) {     /* variable name */
		if (name[0] == '\0')
			strcpy(name, token);
	} else
		prevtoken = YES;
	while ((type = gettoken()) == PARENS || type == BRACKETS || type == '(')
		if (type == PARENS)
			strcat(out, " function returning");
		else if (type == '(') {
			strcat(out, " function expecting");
			parmdcl();
			strcat(out, " and returning");
		} else {
			strcat(out, " array");
			strcat(out, token);
			strcat(out, " of");
		}
}

void errmsg(const char *msg)
{
	printf("%s", msg);
	prevtoken = YES;
}