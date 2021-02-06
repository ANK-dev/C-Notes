#include <stdlib.h>
#include "headers/entab_detab.h"

/* settab: set tab stops in array tab */
void settab(int argc, char **argv, char *tab)
{
	int i, pos;

	if (argc <= 1)           /* default tab stops             */
		for (i = 1; i <= MAXLINE; i++)
			if (i % TABINC)
				tab[i] = YES;
			else
				tab[i] = NO;
	else {                   /* user provided tab stops       */
		for (i = 1; i <= MAXLINE; i++)
			tab[i] = NO;     /* turn off all tab stops        */
		while (--argc > 0) { /* walk through argument list    */
			pos = atoi(*++argv);
			if (pos > 0 && pos <= MAXLINE)
				tab[pos] = YES;
		}
	}
}