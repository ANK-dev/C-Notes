/*
 * Exercise 5-11 - K&R 2nd ED
 * -- ANK-dev
 *
 * entab:  replace spaces with tabs at argv column positions
 */

#include <stdio.h>
#include "headers/entab_detab.h"

/* replace strings of blanks with tabs */
int main(int argc, char **argv)
{
	char tab[MAXLINE+1];

	settab(argc, argv, tab);        /* initialize tab stops  */
	entab(tab);                     /* replace blanks w/ tab */
	return 0;
}

/* entab: replace strings of blanks with tabs and blanks */
void entab(char *tab)
{
	int c, pos;
	int nb = 0;                     /* # of blanks necessary */
	int nt = 0;                     /* # of tabs necessary   */

	for (pos = 1; (c=getchar()) != EOF; pos++)
		if (c == ' ') {
			if (tabpos(pos, tab) == NO)
				++nb;               /* increment # of blanks */
			else {
				nb = 0;             /* reset # of blanks     */
				++nt;               /* one more tab          */
			}
		} else {
			for ( ; nt > 0; nt--)
				putchar('\t');      /* output tab(s)         */
			if (c == '\t')          /* forget the blank(s)   */
				nb = 0;
			else                    /* output blank(s)       */
				for ( ; nb > 0; nb--)
					putchar(' ');
			putchar(c);
			if (c == '\n')
				pos = 0;
			else if (c == '\t')
				while (tabpos(pos, tab) != YES)
					++pos;
		}
}