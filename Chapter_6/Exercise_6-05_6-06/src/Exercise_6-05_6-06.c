#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "headers/getword.h"
#include "headers/struct_proc.h"
#include "headers/ungets.h"

#define MAXWORD 100

void getdef(void);
void undef(char *s);

/* simple version of #define processor */
int main(void)
{
	char w[MAXWORD];
	struct nlist *p;

	while (getword(w, MAXWORD) != EOF)
		if (strcmp(w, "#") == 0)    /* beggining of direct. */
			getdef();
		else if (!isalpha(w[0]))
			printf("%s", w);         /* cannot be defined */
		else if ((p = lookup(w)) == NULL)
			printf("%s", w);        /* not defined */
		else
			ungets(p->defn);        /* push definition */
	return 0;
}

/* getdef: get definition and install it */
void getdef(void)
{
	int i;
	char def[MAXWORD], dir[MAXWORD], name[MAXWORD];

	skipblanks();
	if (!isalpha(getword(dir, MAXWORD)))
		error(dir[0], "getdef: expecting a directive after #");
	else if (strcmp(dir, "define") == 0) {
		skipblanks();
		if (!isalpha(getword(name, MAXWORD)))
			error(name[0], "getdef: non-alpha - name expected");
		else {
			skipblanks();
			for (i = 0; i < MAXWORD; i++)
				if ((def[i] = getch()) == EOF || def[i] == '\n')
					break;      /* end of definition */
			def[i] = '\0';
			if (i <= 0)         /* no definition ? */
				error('\n', "getdef: incomplete define");
			else
				install(name, def);
		}
	} else if (strcmp(dir, "undef") == 0) {
		skipblanks();
		if (!isalpha(getword(name, MAXWORD)))
			error(name[0], "getdef: non-alpha in undef");
		else
			undef(name);
	} else
		error(dir[0], "getdef: expecting a directive after #");
}

/* undef: remove a name and definition from the table */
void undef(char *s)
{
	int h;
	struct nlist *prev, *np;
	extern struct nlist *hashtab[];

	prev = NULL;
	h = hash(s);                /* hash value of string s */
	for (np = hashtab[h]; np != NULL; np = np->next) {
		if (strcmp(s, np->name) == 0)
			break;
		prev = np;              /* remember previous entry */
	}
	if (np != NULL) {           /* found name */
		if (prev == NULL)       /* first in the hash list ? */
			hashtab[h] = np->next;
		else                    /* elsewhere in the hash list */
			prev->next = np->next;
		free((void *) np->name);
		free((void *) np->defn);
		free((void *) np);      /* free allocated structure */
	}
}