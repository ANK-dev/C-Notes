/*
 * Exercise 5-12 - K&R 2nd ED
 * -- ANK-dev
 *
 * detab:  replace tabs with spaces at argv column positions (extra flags)
 */

#include <stdio.h>
#include "headers/entab_detab.h"

/* replace tabs with blanks */
int main(int argc, char **argv)
{
	char tab[MAXLINE+1];

	if (settab(argc, argv, tab) != 0) {
		printf("Invalid argument\n");
		printf("detab - usage: [-m][+n] [d1] [d2] ... [dk]\n"
		       "-m: [optional] starting column,\n"
		       "-n: [optional] column multiple for tabs,\n"
		       "d1 d2 ... dk: [optional] tab stop columns\n");
	}
	detab(tab);                     /* replace tab w/ blanks */
	return 0;
}

/* detab: replace tab with blanks */
void detab(char *tab)
{
	int c, pos = 1;

	while ((c = getchar()) != EOF)
		if (c == '\t') {            /* tab character         */
			do
				putchar(' ');
			while (tabpos(pos++, tab) != YES);
		} else if (c == '\n') {     /* newline character     */
			putchar(c);
			pos = 1;
		} else {                    /* all other characters  */
			putchar(c);
			++pos;
		}
}