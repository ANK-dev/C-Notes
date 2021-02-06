/*
 * Exercise 5-11 - K&R 2nd ED
 * -- ANK-dev
 *
 * detab:  replace tabs with spaces at argv column positions
 */

#include <stdio.h>
#include "headers/entab_detab.h"

/* replace tabs with blanks */
int main(int argc, char **argv)
{
	char tab[MAXLINE+1];

	settab(argc, argv, tab);        /* initialize tab stops  */
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