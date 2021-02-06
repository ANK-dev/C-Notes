#include <stdlib.h>
#include <ctype.h>
#include "headers/entab_detab.h"

/* settab: set tab stops in array tab */
int settab(int argc, char **argv, char *tab)
{
	int i, pos;
	int start_col = 1, col_mult = TABINC;     /* default values */
	int start_col_set = NO, col_mult_set = NO;

	if (argc <= 1)           /* default tab stops               */
		for (i = 1; i <= MAXLINE; i++)
			if (i % TABINC)
				tab[i] = YES;
			else
				tab[i] = NO;
	else {                   /* user provided tab stops        */
		/* check for optional '-m' and '-n' arguments          */
		for (i = 1; i < argc; i++) {
			if (argv[i][0] == '-') {
				if (isdigit(argv[i][1]) && !start_col_set) {
					start_col = atoi(argv[i] + 1);
					start_col_set = YES;
					continue;
				} else {
					return -1;
				}
			} else if (argv[i][0] == '+'){
				if (isdigit(argv[i][1]) && !col_mult_set) {
					col_mult = atoi(argv[i] + 1);
					col_mult_set = YES;
					continue;
				} else {
					return -1;
				}
			}
		}
		for (i = 1; i <= MAXLINE; i++)
			if (col_mult_set && i % col_mult == 0 && i > start_col)
				tab[i] = YES;    /* enable tab stops at col multiples */
			else
				tab[i] = NO;     /* turn off all tab stops            */

		while (--argc > 0) {    /* walk through argument list    */
			argv++;
			if (**argv == '-' || **argv == '+')
				continue;
			pos = atoi(*argv);
			if (pos > 0 && pos <= MAXLINE && pos > start_col)
				tab[pos] = YES;
		}
	}
	return 0;
}