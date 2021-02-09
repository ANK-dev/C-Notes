/*
 * Exercise 5-20 - K&R 2nd ED
 * -- ANK-dev
 *
 * dcl:  convert declarations to words (handle more qualifiers)
 */

#include <stdio.h>
#include <string.h>
#include "headers/dcl.h"

int  tokentype;             /* type of last token           */
char token[MAXTOKEN];       /* last token string            */
char name[MAXTOKEN];        /* identifier name              */
char datatype[MAXTOKEN];    /* data type = char, int, etc.  */
char out[1000];             /* output string                */

/* convert declaration to words */
int main()
{
	while (gettoken() != EOF) {     /* 1st token on line */
		strcpy(datatype, token);    /* is the data type  */
		out[0] = '\0';
		dcl();                      /* parse rest of line */
		if (tokentype != '\n')
			printf("syntax error\n");
		printf("%s: %s %s\n", name, out, datatype);
	}
	return 0;
}